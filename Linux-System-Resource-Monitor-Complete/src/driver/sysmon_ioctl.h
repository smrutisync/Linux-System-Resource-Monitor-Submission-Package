#ifndef SYSMON_IOCTL_H
#define SYSMON_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define SYSMON_MAGIC 'S'

struct sysmon_stats {
    __u64 total_memory_kb;
    __u64 free_memory_kb;
    __u64 available_memory_kb;
    __u64 uptime_seconds;
    __u32 process_count;
};

#define SYSMON_GET_STATS _IOR(SYSMON_MAGIC, 1, struct sysmon_stats)

#endif
