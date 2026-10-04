# 5–10 Minute GitHub Demonstration

## 1. Introduction — 45 seconds
State the title, problem and objective.

## 2. Architecture — 1 minute
Explain:

```text
User
 -> C++ Application
 -> /dev/sysmon
 -> Character Driver
 -> Linux Kernel
 -> System Information
```

## 3. Driver — 1.5 minutes
Show:
- module initialization
- character device
- file operations
- ioctl
- kernel statistics

## 4. C++ Application — 1.5 minutes
Show:
- class structure
- device opening
- ioctl call
- CPU calculation
- menu

## 5. Live Run — 2 minutes
```bash
make
sudo insmod src/driver/sysmon_driver.ko
ls -l /dev/sysmon
sudo ./src/application/sysmon
```

Select the options and explain the output.

## 6. Testing — 1 minute
Show actual test results.

## 7. Limitations/Future Work — 45 seconds
Explain realistic next improvements.
