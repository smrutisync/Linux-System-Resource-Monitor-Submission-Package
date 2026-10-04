# Linux System Resource Monitor

### Custom Linux Character Device Driver with C++ Monitoring Application

A Linux-based System Resource Monitor developed using **Linux Kernel Device Driver Programming, System Programming, and C++**.

The project uses a custom **character device driver** to expose system resource information through `/dev/sysmon`. A user-space C++ application communicates with the driver using `ioctl()` and displays system monitoring information.

---

## 📌 Project Overview

The project demonstrates communication between **user space and kernel space** using a custom Linux character device driver.

### Main Components

1. **Kernel-Space Component**
   - Custom Linux character device driver
   - Creates `/dev/sysmon`
   - Handles device operations
   - Collects system information
   - Provides data to user space through `ioctl()`

2. **User-Space Component**
   - C++17 monitoring application
   - Communicates with `/dev/sysmon`
   - Displays system resource information
   - Provides a command-line monitoring interface

---

## 🎯 Objectives

- Understand Linux kernel module development.
- Implement a custom character device driver.
- Learn kernel-space and user-space communication.
- Use `ioctl()` for device communication.
- Monitor memory and process information.
- Develop a C++ user-space application.
- Understand Linux system programming.
- Perform driver compilation, loading, testing, and unloading.
- Follow a structured six-stage development process.

---

## 🏗️ System Architecture

```text
                 ┌──────────────────────────────┐
                 │       C++ Application        │
                 │          sysmon              │
                 └──────────────┬───────────────┘
                                │
                                │ ioctl()
                                ▼
                 ┌──────────────────────────────┐
                 │       /dev/sysmon            │
                 │    Character Device Node     │
                 └──────────────┬───────────────┘
                                │
                                ▼
                 ┌──────────────────────────────┐
                 │    Linux Kernel Driver       │
                 │      sysmon_driver.ko        │
                 ├──────────────────────────────┤
                 │ Device initialization        │
                 │ Device operations            │
                 │ ioctl handling               │
                 │ System information           │
                 └──────────────┬───────────────┘
                                │
                                ▼
                 ┌──────────────────────────────┐
                 │       Linux Kernel           │
                 │ Memory / Process information │
                 └──────────────────────────────┘
```

---

## 📁 Project Structure

```text
Linux-System-Resource-Monitor-Complete/
│
├── README.md
├── Makefile
├── .gitignore
│
├── src/
│   ├── driver/
│   │   ├── Makefile
│   │   ├── sysmon_driver.c
│   │   └── sysmon_driver.ko
│   │
│   └── application/
│       ├── Makefile
│       ├── main.cpp
│       ├── SystemMonitor.cpp
│       ├── SystemMonitor.h
│       ├── MemoryMonitor.cpp
│       ├── MemoryMonitor.h
│       ├── ProcessMonitor.cpp
│       ├── ProcessMonitor.h
│       └── sysmon
│
├── docs/
├── scripts/
└── tests/
    ├── test_driver.sh
    └── test_application.sh
```

---

# ⚙️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Linux kernel driver |
| C++17 | User-space monitoring application |
| Linux Kernel | Kernel-space development |
| Makefile | Build automation |
| Character Device Driver | Kernel-user communication |
| `ioctl()` | Device communication |
| GCC / G++ | Compilation |
| Bash | Testing and automation |
| Git / GitHub | Version control |

---

# 🔑 Key Features

### Kernel Driver

- Custom Linux character device driver.
- Dynamic device number allocation.
- Device class and device creation.
- Creates `/dev/sysmon`.
- Supports device file operations.
- Uses `ioctl()` for communication.
- Retrieves system memory information.
- Supports module loading and unloading.

### C++ Application

- User-space C++17 application.
- Communicates with the kernel driver.
- Uses `/dev/sysmon`.
- Displays system resource information.
- Uses modular C++ classes for monitoring functionality.

---

# 💾 Memory Monitoring

The driver uses Linux kernel memory information facilities to obtain system memory statistics, including information such as:

- Total memory
- Available memory
- Used memory
- Memory utilization

---

# 🔄 Process Monitoring

The application contains a process monitoring component using:

```text
ProcessMonitor.cpp
ProcessMonitor.h
```

The component is designed to provide information about running processes and demonstrate system-level process monitoring.

---

# 🛠️ Build Instructions

## Prerequisites

A compatible Linux environment and kernel development environment are required.

Install common development tools:

```bash
sudo apt update
sudo apt install build-essential flex bison libelf-dev
```

Check the running kernel:

```bash
uname -r
```

For kernel modules, the driver must be built against a compatible kernel source/build configuration.

---

# 🔨 Build the Project

Navigate to the project directory:

```bash
cd Linux-System-Resource-Monitor-Complete
```

Build the driver and application:

```bash
make
```

Expected outputs:

```text
src/driver/sysmon_driver.ko
src/application/sysmon
```

---

# 🚀 Running the Project

## 1. Load the Kernel Module

```bash
sudo insmod src/driver/sysmon_driver.ko
```

Verify:

```bash
lsmod | grep sysmon_driver
```

## 2. Verify the Device

```bash
ls -l /dev/sysmon
```

Expected:

```text
/dev/sysmon
```

## 3. Run the Application

```bash
cd src/application
sudo ./sysmon
```

The application communicates with the kernel driver through `/dev/sysmon`.

---

# 🧪 Testing

Run the supplied tests:

```bash
bash tests/test_driver.sh
```

```bash
bash tests/test_application.sh
```

Manual checks:

```bash
lsmod | grep sysmon_driver
ls -l /dev/sysmon
dmesg | tail -30
./src/application/sysmon
```

---

# 🔴 Unloading the Driver

After exiting the application:

```bash
sudo rmmod sysmon_driver
```

Verify:

```bash
lsmod | grep sysmon_driver
```

---

# 📊 Testing Checklist

| Test | Expected Result |
|---|---|
| Driver compilation | `sysmon_driver.ko` generated |
| Application compilation | `sysmon` generated |
| Driver loading | Module appears in `lsmod` |
| Device creation | `/dev/sysmon` exists |
| IOCTL communication | Application communicates with driver |
| Memory monitoring | Memory information displayed |
| Process monitoring | Process information available |
| Application execution | Application runs successfully |
| Driver unloading | Module removed successfully |

> Test results should be recorded from actual execution in the target Linux environment.

---

# 📚 Six-Stage Development Process

## Stage 1 — Project Introduction

Define the problem, motivation, objectives, scope, technologies, and expected outcome.

## Stage 2 — Requirements & Development Plan

Identify Linux, kernel, compiler, build-tool, and development requirements and prepare the development plan.

## Stage 3 — System Design & Architecture

Design the user-space to kernel-space communication architecture using a character device and `ioctl()`.

```text
User Application
       ↓
   ioctl()
       ↓
Character Device
       ↓
Kernel Driver
       ↓
Linux Kernel
```

## Stage 4 — Initial Implementation & Prototype

Implement:

- Character device driver
- Device registration
- `/dev/sysmon`
- IOCTL interface
- Memory monitoring
- Process monitoring
- C++ application
- Makefiles

## Stage 5 — Testing, Integration & Improvement

Verify:

- Driver compilation
- Module loading
- Device creation
- IOCTL communication
- Memory monitoring
- Process monitoring
- Application execution
- Driver unloading
- Error handling

## Stage 6 — Final Integration & Presentation

Prepare:

- Source code
- Kernel driver
- C++ application
- Test scripts
- Documentation
- README
- Evidence/screenshots
- GitHub repository
- Final demonstration

---

# 📸 Evidence & Demonstration

Recommended evidence should be captured from actual execution:

### Project Compilation

```bash
make
```

### Driver Module

```bash
lsmod | grep sysmon_driver
```

### Device Node

```bash
ls -l /dev/sysmon
```

### Kernel Messages

```bash
dmesg | tail -30
```

### Application

```bash
./src/application/sysmon
```

### Driver Removal

```bash
sudo rmmod sysmon_driver
```

**Do not use fabricated screenshots or test results. Evidence should show real execution output.**

---

# 🐛 Troubleshooting

## `/dev/sysmon` does not exist

Check:

```bash
lsmod | grep sysmon_driver
```

Load the module:

```bash
sudo insmod src/driver/sysmon_driver.ko
```

Then:

```bash
ls -l /dev/sysmon
```

## Invalid module format

Check:

```bash
uname -r
modinfo src/driver/sysmon_driver.ko | grep vermagic
```

The module must match the running kernel version and compatible kernel configuration.

## Permission denied

Try:

```bash
sudo ./src/application/sysmon
```

## Driver cannot be removed

Check:

```bash
sudo lsof /dev/sysmon
```

Stop applications using the device, then:

```bash
sudo rmmod sysmon_driver
```

---

# 🧠 Learning Outcomes

This project demonstrates:

- Linux kernel programming
- Character device drivers
- Kernel modules
- Device registration
- User-space/kernel-space communication
- IOCTL mechanisms
- Linux memory management interfaces
- Process monitoring
- C++ system programming
- Makefile-based compilation
- Linux debugging
- Shell scripting
- Git and GitHub workflow

---

# 📦 Project Deliverables

- Linux kernel driver source
- C++ application source
- Makefiles
- Testing scripts
- Six-stage documentation
- README
- Architecture/design documentation
- Evidence and testing documentation
- GitHub repository

Runtime-generated files such as `.ko` modules and binaries can be regenerated using the build instructions.

---

# 👨‍💻 Author

**Smruti Ranjan Nayak**

B.Tech — Computer Science & Engineering

Siksha 'O' Anusandhan (SOA) University, Bhubaneswar

---

# 📄 License

This project was developed for educational and academic purposes.
