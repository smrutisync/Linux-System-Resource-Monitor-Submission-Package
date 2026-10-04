# Stage 1 — Project Introduction

## Project Title

**Linux System Resource Monitor Using a Custom Character Device Driver**

## 1. Introduction

This project is a Linux-based system monitoring application that demonstrates communication between user space and kernel space. A custom Linux character device driver provides selected system statistics to a C++ application.

## 2. Problem Statement

Operating-system resources such as memory, CPU utilization, running processes and system uptime are useful for understanding the state of a computer. The project demonstrates how Linux kernel functionality can be accessed through a custom device-driver interface rather than building only a normal user-space application.

## 3. Objectives

- Develop a Linux kernel module.
- Implement a character device.
- Create `/dev/sysmon`.
- Demonstrate kernel/user-space communication.
- Use C++ for the user-space application.
- Display CPU, memory, process and uptime information.
- Apply software/system architecture concepts.
- Maintain the project using Git and GitHub.

## 4. Scope

The project focuses on a local Linux computer. It is an educational system-programming project and is not intended to replace production monitoring tools.

## 5. Expected Outcome

The final system should load a custom kernel module, create a character device, allow the C++ application to request statistics, and display those statistics in a terminal interface.

## 6. Application

The project can be used as an educational demonstration of Linux kernel modules, character drivers, system programming, hardware/software interaction and C++ programming.

## 7. Stage-1 Evidence

Add your own screenshots/notes under `evidence/stage-1/`.
