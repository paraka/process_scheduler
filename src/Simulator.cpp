#include <iostream>
#include "Queue.h"
#include "Process.h"
#include "Utils.h"

namespace
{
    static const uint64_t EXECUTION_TIME_SECONDS = 10;
    static const uint32_t MILLISECONS_IN_A_SECOND = 1000;
    static const uint32_t MICROSECONS_IN_A_SECOND = 1000000;
}

int main()
{
    Process p1(1,10.5);
    Process p2(2,1.6);
    Process p3(6,20.5);
    Process p4(7,6.6);
    p3.setPriority(10);
    p4.setPriority(20);

    auto queue = makeQueue<Process>();

    uint64_t seconds = Utils::getTimeStamp();
    uint64_t stopTS = Utils::getTimeStamp() + (EXECUTION_TIME_SECONDS * MILLISECONS_IN_A_SECOND);

    auto t1 = Utils::Time();

    while (seconds <= stopTS)
    {
        queue->push(p1);
        queue->push(p2);
        queue->push(p3);
        queue->push(p4);

        queue->debug();

        std::cout << "Size: " << queue->size() << std::endl;
        auto ret = queue->pop(PopCriteria::PRIORITY);
        auto ret2 = queue->pop(PopCriteria::ARRIVAL_TIME);

        std::cout << (*ret).getPriority() << " " << (*ret2).getTimeStamp() << std::endl;

        std::cout << "Size: " << queue->size() << std::endl;

        queue->debug();
        seconds = Utils::getTimeStamp();
    }

    auto t2 = Utils::Time();

    std::cout << "Executing stuff for " << Utils::Diff(t1, t2) / MICROSECONS_IN_A_SECOND << " seconds" << std::endl;

    return 0;
}
