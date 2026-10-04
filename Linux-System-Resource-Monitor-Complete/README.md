# Linux System Resource Monitor Using a Custom Character Device Driver

**Individual Capstone Project**

## 1. Overview

This project demonstrates Linux system programming through a custom character device driver and a C++ user-space application.

The kernel module creates `/dev/sysmon`. The C++ application opens this device and uses `ioctl()` to request system statistics collected by the driver. CPU utilization is calculated in user space using `/proc/stat`.

## 2. Concepts Demonstrated

- Linux operating system
- C programming
- C++ programming and classes
- Linux kernel modules
- Character device drivers
- Kernel/user-space communication
- `ioctl()`
- `copy_to_user()`
- Linux `/proc` filesystem
- System information APIs
- Data structures
- Makefiles
- Git/GitHub
- Software/system architecture
- Testing and debugging

## 3. Architecture

```text
+---------------------------+
|           User            |
+-------------+-------------+
              |
              v
+---------------------------+
|     C++ Application       |
|       User Space          |
+-------------+-------------+
              |
          ioctl()
              |
              v
+---------------------------+
|       /dev/sysmon         |
|     Character Device      |
+-------------+-------------+
              |
              v
+---------------------------+
|     Linux Kernel Module   |
|       sysmon_driver.c     |
+-------------+-------------+
              |
        +-----+------+
        |            |
        v            v
   System Info   Process Count
        |
        v
+---------------------------+
|   Linux OS / Hardware     |
|       CPU / RAM           |
+---------------------------+

CPU utilization is calculated by the application from /proc/stat.
```

## 4. Repository Structure

```text
Linux-System-Resource-Monitor-Complete/
├── README.md
├── Makefile
├── .gitignore
├── src/
│   ├── driver/
│   │   ├── sysmon_driver.c
│   │   ├── sysmon_ioctl.h
│   │   └── Makefile
│   └── application/
│       ├── main.cpp
│       ├── SystemMonitor.cpp
│       ├── SystemMonitor.h
│       ├── MemoryMonitor.cpp
│       ├── MemoryMonitor.h
│       ├── ProcessMonitor.cpp
│       ├── ProcessMonitor.h
│       └── Makefile
├── tests/
├── docs/
└── evidence/
```

## 5. Requirements

Recommended Ubuntu/Debian environment:

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) git
```

You need:
- Linux
- GCC/G++
- GNU Make
- Matching kernel headers
- Git

## 6. Build

From the project root:

```bash
make
```

Or separately:

```bash
make driver
make app
```

## 7. Load the Driver

```bash
sudo insmod src/driver/sysmon_driver.ko
```

Verify:

```bash
lsmod | grep sysmon
ls -l /dev/sysmon
dmesg | tail -n 20
```

## 8. Run the Application

```bash
sudo ./src/application/sysmon
```

Example menu:

```text
========================================
       LINUX SYSTEM RESOURCE MONITOR
========================================
1. Show CPU Usage
2. Show Kernel Statistics
3. Show All
4. Exit
========================================
Enter choice:
```

## 9. Unload the Driver

After exiting the application:

```bash
sudo rmmod sysmon_driver
```

Verify:

```bash
ls -l /dev/sysmon
lsmod | grep sysmon
```

## 10. Testing

Run:

```bash
bash tests/test_driver.sh
bash tests/test_application.sh
```

The tests require the driver to be loaded where applicable.

## 11. Documentation

The project follows the required six-stage process:

1. Project Introduction
2. Requirements & Development Plan
3. System Design & Architecture
4. Initial Implementation & Prototype
5. Testing, Integration & Improvement
6. Final Implementation & Presentation

See the `docs/` directory.

## 12. Important Safety Note

Kernel modules execute with kernel privileges. Test in a Linux VM if possible. Build against the kernel headers of the system on which you will demonstrate the project.

## 13. Author

Replace with your details:

- Name: Smruti Ranjan Nayak
- Roll Number: 2341014072
- Department: B.Tech CSE
- Institution: Siksha 'O' Anusandhan
