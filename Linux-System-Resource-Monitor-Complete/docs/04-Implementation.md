# Stage 4 — Initial Implementation & Prototype

## 1. Build

```bash
make clean
make
```

## 2. Load Driver

```bash
sudo insmod src/driver/sysmon_driver.ko
```

## 3. Verify Driver

```bash
lsmod | grep sysmon
ls -l /dev/sysmon
dmesg | tail -n 20
```

## 4. Run Application

```bash
sudo ./src/application/sysmon
```

## 5. Prototype Demonstration

Demonstrate:

1. Kernel module loading.
2. Character-device creation.
3. C++ application opening the device.
4. ioctl communication.
5. CPU monitoring.
6. Memory/process/uptime output.

## 6. Development Issues

Record actual errors and solutions here.

## 7. Evidence

Place your own screenshots and terminal output in `evidence/stage-4/`.
