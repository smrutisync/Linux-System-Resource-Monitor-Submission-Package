# Stage 3 — System Design & Architecture

## 1. High-Level Architecture

```text
+-------------------+
|       USER        |
+---------+---------+
          |
          v
+-------------------+
| C++ Application   |
|    User Space     |
+---------+---------+
          |
       ioctl()
          |
          v
+-------------------+
|    /dev/sysmon    |
| Character Device  |
+---------+---------+
          |
          v
+-------------------+
| Linux Kernel      |
| Character Driver  |
+---------+---------+
          |
     +----+----+------+
     |         |      |
     v         v      v
   Memory   Processes Uptime

C++ application separately reads /proc/stat
for CPU utilization.
```

## 2. Components

### C++ Application
Provides the terminal interface and requests information.

### Character Device
Provides the `/dev/sysmon` interface.

### Kernel Module
Implements the character device and gathers selected kernel statistics.

### Linux Kernel
Provides operating-system information and manages hardware resources.

## 3. Hardware/Software Relationship

```text
CPU / RAM / Hardware
        |
        v
Linux Kernel
        |
        v
Kernel Driver
        |
        v
C++ User Application
        |
        v
User
```

## 4. Data Structure

The driver and application share `struct sysmon_stats`:

- total memory
- free memory
- available memory
- uptime
- process count

## 5. UML

The Mermaid files in `docs/diagrams/` provide the source for:

- Architecture
- Class diagram
- Sequence diagram
- State machine diagram

Export them as images for the final report.

## 6. Git Strategy

Use meaningful commits at every real milestone.

Example:

```text
Initial project structure
Add project requirements
Add system architecture
Implement kernel module
Implement character device
Implement ioctl
Implement C++ application
Add monitoring
Add tests
Complete documentation
```
