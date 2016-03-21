#include <iostream>
#include "Algorithms.h"
#include "Stats.h"
#include "Utils.h"

void Algorithms::Execute(QueuePtr queue, ComparatorFunc func, Stats& stats)
{
    while (!queue->empty())
    {
        auto process = queue->pop(func);
        ++stats.num_process;
        stats.total_cpu +=  (*process).getCPUPercent();
        stats.total_work_units += (*process).getWorkUnits();
    }
}

void Algorithms::FCFS(QueuePtr queue, Stats& stats)
{
    std::cout << "FCFS" << std::endl;

    auto compFCFS = [](const Process &a, const Process &b ) { return a.getTimeStamp() < b.getTimeStamp(); };

    Algorithms::Execute(queue, compFCFS, stats);

}

void Algorithms::RR(QueuePtr queue, Stats& stats)
{
    // Set nice of 2 by default
    static const uint32_t nice = 2;

    std::cout << "RR" << std::endl;
    auto compRR = [](const Process &a, const Process &b ) { return a.getTimeStamp() < b.getTimeStamp(); };

    while (!queue->empty())
    {
        auto process = queue->pop(compRR);
        auto work_units = (*process).getWorkUnits();
        if (work_units > 0)
        {
            (*process).setWorkUnits(work_units - nice);
            (*process).setTimeStamp(Utils::getTimeStamp());
            queue->push(*process);
        }
        else
        {
            ++stats.num_process;
            stats.total_cpu +=  (*process).getCPUPercent();
            stats.total_work_units += (*process).getWorkUnits();
        }
    }
}

void Algorithms::PriorityQueue(QueuePtr queue, Stats& stats)
{
    std::cout << "PQ" << std::endl;

    auto compPQ = [](const Process &a, const Process &b ) { return a.getPriority() > b.getPriority(); };

    Algorithms::Execute(queue, compPQ, stats);
}

void Algorithms::SJK(QueuePtr queue, Stats& stats)
{
    std::cout << "SJK" << std::endl;

    auto compSJK = [](const Process &a, const Process &b ) { return a.getWorkUnits() < b.getWorkUnits(); };

    Algorithms::Execute(queue, compSJK, stats);
}
