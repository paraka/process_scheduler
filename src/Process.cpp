#include <iostream>
#include "Process.h"
#include "Utils.h"

Process::Process(uint32_t pid, double cpu_percent) : 
                    pid_(pid), 
                    cpu_percent_(cpu_percent),
                    priority_(-1) 
{
    auto random = Utils::getRandom<double>(1, 10);
    timestamp_ = Utils::getTimeStamp() + static_cast<uint64_t>(random);
}

void Process::debugProcess()
{
    std::cout << "PID: " << pid_ << " TIMESTAMP: " << timestamp_ << " CPU_PERCENT: " << cpu_percent_ << " PRIORITY: " << priority_ << std::endl;
}
