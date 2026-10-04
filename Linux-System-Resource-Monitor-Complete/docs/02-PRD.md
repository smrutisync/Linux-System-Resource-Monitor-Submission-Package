# Stage 2 — Project Requirements Document

## 1. Functional Requirements

| ID | Requirement |
|---|---|
| FR-01 | Load a Linux kernel module |
| FR-02 | Register a character device |
| FR-03 | Create `/dev/sysmon` |
| FR-04 | Open the device from user space |
| FR-05 | Request statistics using `ioctl()` |
| FR-06 | Return memory information |
| FR-07 | Return process count |
| FR-08 | Return system uptime |
| FR-09 | Calculate CPU utilization from `/proc/stat` |
| FR-10 | Display the information through a C++ terminal application |
| FR-11 | Handle invalid menu input |
| FR-12 | Unload the driver cleanly |

## 2. Non-Functional Requirements

- Linux compatibility
- Readable and modular code
- Basic error handling
- Maintainability
- Reliable cleanup
- Git-based version control
- Documentation

## 3. Hardware Requirements

- Linux-compatible computer or virtual machine
- At least 2 GB RAM recommended

## 4. Software Requirements

- Linux
- GCC
- G++
- GNU Make
- Matching Linux kernel headers
- Git

## 5. Main Modules

1. Kernel module
2. Character device
3. ioctl interface
4. C++ application
5. CPU monitoring
6. Testing/documentation

## 6. Deliverables

- Source code
- README
- PRD
- Architecture documentation
- UML diagrams
- Test results
- GitHub repository
- Final report
- Demonstration

## 7. Development Timeline

### Stage 1
Project idea and introduction.

### Stage 2
Requirements and development plan.

### Stage 3
Architecture, UML and implementation plan.

### Stage 4
Initial implementation and prototype.

### Stage 5
Testing, integration and improvements.

### Stage 6
Final implementation and presentation.
