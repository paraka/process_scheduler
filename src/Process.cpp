#include <chrono>
#include <iostream>
#include "Process.h"
#include "Utils.h"

Process::Process(uint32_t pid, double cpu_percent) : 
                    pid_(pid), 
                    cpu_percent_(cpu_percent),
                    priority_(-1) 
{
    auto random = Utils::getRandom<double>(1, 10);
    timestamp_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<uint64_t>(random);
}

void Process::debugProcess()
{
    std::cout << "PID: " << pid_ << " TIMESTAMP: " << timestamp_ << " CPU_PERCENT: " << cpu_percent_ << " PRIORITY: " << priority_ << std::endl;
}
