#include "ProcessGenerator.h"
#include "Process.h"
#include "Utils.h"
#include "Queue.h"


ProcessGenerator::~ProcessGenerator()
{
    end_ = true;
    th_.join();
}
     
ProcessGeneratorPtr ProcessGenerator::createGenerator(QueuePtr q)
{
    ProcessGeneratorPtr aPtr(new ProcessGenerator(q));
    aPtr->th_ = std::thread(&ProcessGenerator::run, aPtr.get());
    return aPtr;
}

void ProcessGenerator::run()
{
    uint32_t pid = 1;
    while (!end_)
    {
        //Generate process and enqueue
        double percent_cpu = Utils::getRandom<double>(1.0, 20.0);
        Process p(pid, percent_cpu);
        uint32_t priority = static_cast<uint32_t>(Utils::getRandom<double>(1.0, 20.0));
        p.setPriority(priority);
        uint32_t work_units = static_cast<uint32_t>(Utils::getRandom<double>(1.0, 10.0));
        queue_->push(p);
        ++pid;
    }
}
