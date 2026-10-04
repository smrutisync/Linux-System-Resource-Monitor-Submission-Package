/*
 * Linux System Resource Monitor
 * Custom character device driver.
 */

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sysinfo.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/ktime.h>
#include <linux/string.h>

#include "sysmon_ioctl.h"

#define DEVICE_NAME "sysmon"
#define CLASS_NAME "sysmon"

static dev_t dev_number;
static struct cdev sysmon_cdev;
static struct class *sysmon_class;

static int sysmon_open(struct inode *inode, struct file *file)
{
    pr_info("sysmon: device opened\n");
    return 0;
}

static int sysmon_release(struct inode *inode, struct file *file)
{
    pr_info("sysmon: device closed\n");
    return 0;
}

static long sysmon_ioctl(struct file *file, unsigned int command,
                         unsigned long arg)
{
    struct sysmon_stats stats;
    struct sysinfo info;
    struct task_struct *task;
    u32 process_count = 0;

    if (_IOC_TYPE(command) != SYSMON_MAGIC)
        return -EINVAL;

    if (command != SYSMON_GET_STATS)
        return -EINVAL;

    memset(&stats, 0, sizeof(stats));

    si_meminfo(&info);

    for_each_process(task)
        process_count++;

    stats.total_memory_kb =
        (u64)info.totalram * (u64)info.mem_unit / 1024;

    stats.free_memory_kb =
        (u64)info.freeram * (u64)info.mem_unit / 1024;

    /*
     * This educational project reports free RAM as the available
     * memory value. A production monitor would use a more complete
     * memory-availability calculation.
     */
    stats.available_memory_kb = stats.free_memory_kb;

    stats.uptime_seconds = ktime_get_boottime_seconds();
    stats.process_count = process_count;

    if (copy_to_user((void __user *)arg, &stats, sizeof(stats)))
        return -EFAULT;

    return 0;
}

static const struct file_operations sysmon_fops = {
    .owner = THIS_MODULE,
    .open = sysmon_open,
    .unlocked_ioctl = sysmon_ioctl,
    .release = sysmon_release,
};

static int __init sysmon_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("sysmon: alloc_chrdev_region failed\n");
        return ret;
    }

    cdev_init(&sysmon_cdev, &sysmon_fops);
    sysmon_cdev.owner = THIS_MODULE;

    ret = cdev_add(&sysmon_cdev, dev_number, 1);
    if (ret < 0) {
        pr_err("sysmon: cdev_add failed\n");
        unregister_chrdev_region(dev_number, 1);
        return ret;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    sysmon_class = class_create(CLASS_NAME);
#else
    sysmon_class = class_create(THIS_MODULE, CLASS_NAME);
#endif

    if (IS_ERR(sysmon_class)) {
        pr_err("sysmon: class_create failed\n");
        cdev_del(&sysmon_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(sysmon_class);
    }

    if (IS_ERR(device_create(sysmon_class, NULL, dev_number, NULL,
                             DEVICE_NAME))) {
        pr_err("sysmon: device_create failed\n");
        class_destroy(sysmon_class);
        cdev_del(&sysmon_cdev);
        unregister_chrdev_region(dev_number, 1);
        return -ENODEV;
    }

    pr_info("sysmon: module loaded successfully\n");
    pr_info("sysmon: major=%d minor=%d\n",
            MAJOR(dev_number), MINOR(dev_number));

    return 0;
}

static void __exit sysmon_exit(void)
{
    device_destroy(sysmon_class, dev_number);
    class_destroy(sysmon_class);
    cdev_del(&sysmon_cdev);
    unregister_chrdev_region(dev_number, 1);

    pr_info("sysmon: module unloaded\n");
}

module_init(sysmon_init);
module_exit(sysmon_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smruti Ranjan Nayak");
MODULE_DESCRIPTION("Linux system resource monitoring character device");
MODULE_VERSION("1.0");
