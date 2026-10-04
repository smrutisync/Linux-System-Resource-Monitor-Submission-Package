#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

class SystemMonitor {
public:
    SystemMonitor();
    ~SystemMonitor();

    bool openDevice();
    void closeDevice();
    void run();

private:
    int deviceFd;

    void showMenu();
    void showKernelStats();
    void showCpuUsage();

    double readCpuUsage();
    void printLine() const;
};

#endif
