#include <iostream>
#include "Algorithms.h"
#include "Stats.h"

void Algorithms::FCFS(QueuePtr queue, Stats& stats)
{
    std::cout << "FCFS" << std::endl;
    
    auto compFCFS = [](const Process &a, const Process &b ) { return a.getTimeStamp() < b.getTimeStamp(); };

    while (!queue->empty())
    {
        auto process = queue->pop(compFCFS);
        ++stats.num_process;
        stats.total_cpu +=  (*process).getCPUPercent();
    }
}

void Algorithms::RR(QueuePtr queue, Stats& stats)
{
    std::cout << "RR" << std::endl;
}

void Algorithms::PriorityQueue(QueuePtr queue, Stats& stats)
{
    std::cout << "PQ" << std::endl;
}

void Algorithms::SJK(QueuePtr queue, Stats& stats)
{
    std::cout << "SJK" << std::endl;
}

