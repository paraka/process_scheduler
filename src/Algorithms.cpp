#include <iostream>
#include "Algorithms.h"
#include "Stats.h"

void Algorithms::FCFS(QueuePtr queue, Stats& stats)
{
    std::cout << "FCFS" << std::endl;
    
    while (!queue->empty())
    {
        auto process = queue->pop(PopCriteria::ARRIVAL_TIME);
        ++stats.num_process;
        stats.total_cpu +=  (*process).getCPUPercent();
        //(*process).debugProcess();
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

