#ifndef _ALGORITHM_SIMULATOR_H_
#define _ALGORITHM_SIMULATOR_H_

#include <thread>
#include "Stats.h"

template <typename T> class Queue;
class Process;

class AlgorithmSimulator
{
    using QueuePtr = std::shared_ptr<Queue<Process>>;
    using AlgorithCallBack = std::function<void(QueuePtr queue, Stats &stats)>;

public:
    explicit AlgorithmSimulator(AlgorithCallBack algorithm): callback_(algorithm) {}

    void Simulate(QueuePtr queue)
    {
        //callback_(queue);
        task_ = std::thread(callback_, queue, std::ref(stats_));
    }

    void Stop()
    {
        task_.join();
    }

    const Stats & getStats() const
    {
        return stats_;
    }

private:
    AlgorithCallBack callback_; 
    Stats stats_;
    std::thread task_;
};

#endif // _ALGORITHM_SIMULATOR_H_
