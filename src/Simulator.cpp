#include <iostream>
#include "Queue.h"
#include "Process.h"

int main()
{
    Process p1(1,10.5);
    Process p2(2,1.6);
    Process p3(6,20.5);
    Process p4(7,6.6);
    p3.setPriority(10);
    p4.setPriority(20);

    Queue<Process> queue;

    queue.push(p1);
    queue.push(p2);
    queue.push(p3);
    queue.push(p4);

    queue.debug();

    std::cout << "Size: " << queue.size() << std::endl;
    auto ret = queue.pop(PopCriteria::PRIORITY);
    auto ret2 = queue.pop(PopCriteria::ARRIVAL_TIME);

    std::cout << (*ret).getPriority() << " " << (*ret2).getTimeStamp() << std::endl;

    std::cout << "Size: " << queue.size() << std::endl;

    queue.debug();

    return 0;
}
