#include "SystemMonitor.h"
#include "../driver/sysmon_ioctl.h"

#include <cerrno>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

SystemMonitor::SystemMonitor() : deviceFd(-1)
{
}

SystemMonitor::~SystemMonitor()
{
    closeDevice();
}

bool SystemMonitor::openDevice()
{
    deviceFd = open("/dev/sysmon", O_RDONLY);

    if (deviceFd < 0) {
        std::cerr << "Unable to open /dev/sysmon: "
                  << std::strerror(errno) << '\n';
        return false;
    }

    return true;
}

void SystemMonitor::closeDevice()
{
    if (deviceFd >= 0) {
        close(deviceFd);
        deviceFd = -1;
    }
}

void SystemMonitor::printLine() const
{
    std::cout << "========================================\n";
}

void SystemMonitor::showMenu()
{
    std::cout << '\n';
    printLine();
    std::cout << "       LINUX SYSTEM RESOURCE MONITOR\n";
    printLine();
    std::cout << "1. Show CPU Usage\n";
    std::cout << "2. Show Kernel Statistics\n";
    std::cout << "3. Show All\n";
    std::cout << "4. Exit\n";
    printLine();
}

void SystemMonitor::showKernelStats()
{
    if (deviceFd < 0) {
        std::cout << "Device is not open.\n";
        return;
    }

    sysmon_stats stats{};

    if (ioctl(deviceFd, SYSMON_GET_STATS, &stats) < 0) {
        std::cerr << "ioctl failed: " << std::strerror(errno) << '\n';
        return;
    }

    const double totalGb =
        static_cast<double>(stats.total_memory_kb) / (1024.0 * 1024.0);

    const double freeGb =
        static_cast<double>(stats.free_memory_kb) / (1024.0 * 1024.0);

    std::cout << "\n--- Kernel Statistics ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Memory      : " << totalGb << " GB\n";
    std::cout << "Free Memory       : " << freeGb << " GB\n";
    std::cout << "Available Memory  : "
              << static_cast<double>(stats.available_memory_kb)
                     / (1024.0 * 1024.0)
              << " GB\n";
    std::cout << "System Uptime     : "
              << stats.uptime_seconds << " seconds\n";
    std::cout << "Running Processes : "
              << stats.process_count << '\n';
}

double SystemMonitor::readCpuUsage()
{
    auto readCpu = [](unsigned long long& idle,
                      unsigned long long& total) -> bool {
        std::ifstream file("/proc/stat");

        if (!file.is_open())
            return false;

        std::string cpu;
        unsigned long long user = 0;
        unsigned long long nice = 0;
        unsigned long long system = 0;
        unsigned long long idleTime = 0;
        unsigned long long iowait = 0;
        unsigned long long irq = 0;
        unsigned long long softirq = 0;
        unsigned long long steal = 0;

        file >> cpu >> user >> nice >> system >> idleTime
             >> iowait >> irq >> softirq >> steal;

        if (cpu != "cpu")
            return false;

        idle = idleTime + iowait;
        total = user + nice + system + idleTime +
                iowait + irq + softirq + steal;

        return true;
    };

    unsigned long long idle1 = 0;
    unsigned long long total1 = 0;
    unsigned long long idle2 = 0;
    unsigned long long total2 = 0;

    if (!readCpu(idle1, total1))
        return -1.0;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (!readCpu(idle2, total2))
        return -1.0;

    const unsigned long long totalDelta = total2 - total1;
    const unsigned long long idleDelta = idle2 - idle1;

    if (totalDelta == 0)
        return 0.0;

    const double busy =
        static_cast<double>(totalDelta - idleDelta);

    return (busy / static_cast<double>(totalDelta)) * 100.0;
}

void SystemMonitor::showCpuUsage()
{
    const double usage = readCpuUsage();

    if (usage < 0.0) {
        std::cout << "Unable to read CPU statistics.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2)
              << "\nCPU Usage: " << usage << " %\n";
}

void SystemMonitor::run()
{
    if (!openDevice()) {
        std::cout << "Load the kernel module before running the application.\n";
        return;
    }

    int choice = 0;

    while (choice != 4) {
        showMenu();
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            showCpuUsage();
            break;

        case 2:
            showKernelStats();
            break;

        case 3:
            showCpuUsage();
            showKernelStats();
            break;

        case 4:
            std::cout << "Exiting application...\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }
    }
}
