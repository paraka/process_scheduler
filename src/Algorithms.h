#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <memory>
#include "Queue.h"
#include "Process.h"

enum class EAlgorithms
{
    FCFS = 0,
    RR,
    PQ,
    SJK
};

struct Stats;

class Algorithms
{
    using QueuePtr = std::shared_ptr<Queue<Process>>;

public:
    static void FCFS(QueuePtr queue, Stats& stats);
    static void RR(QueuePtr queue, Stats& stats);
    static void PriorityQueue(QueuePtr queue, Stats& stats);
    static void SJK(QueuePtr queue, Stats& stats);
};

#endif // _ALGORITHMS_H_
