CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

TARGET := sysmon
SOURCES := main.cpp SystemMonitor.cpp MemoryMonitor.cpp ProcessMonitor.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
