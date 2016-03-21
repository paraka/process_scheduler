#include <iostream>
#include "Queue.h"
#include "Process.h"
#include "Utils.h"
#include "AlgorithmSimulator.h"
#include "ProcessGenerator.h"
#include "Algorithms.h"

namespace
{
    static const uint64_t EXECUTION_TIME_SECONDS = 10;
    static const uint32_t MILLISECONS_IN_A_SECOND = 1000;
    static const uint32_t MICROSECONS_IN_A_SECOND = 1000000;
}

auto bindSimulator(EAlgorithms algorithm)
{
    switch (algorithm)
    {
        case EAlgorithms::FCFS:
            {
                AlgorithmSimulator fcfs(std::bind(&Algorithms::FCFS, std::placeholders::_1, std::placeholders::_2));
                return fcfs;
            }
        case EAlgorithms::RR:
            {
                AlgorithmSimulator rr(std::bind(&Algorithms::RR, std::placeholders::_1, std::placeholders::_2));
                return rr;
            }
        case EAlgorithms::PQ:
            {
                AlgorithmSimulator pq(std::bind(&Algorithms::PriorityQueue, std::placeholders::_1, std::placeholders::_2));
                return pq;
            }
        case EAlgorithms::SJK:
            {
                AlgorithmSimulator sjk(std::bind(&Algorithms::PriorityQueue, std::placeholders::_1, std::placeholders::_2));
                return sjk;
            }
        default:
            throw std::logic_error("Invalid algorithm...");
    }
}

void ShowStats(const Stats &stats, const std::string &alg)
{
    std::cout << "**************************************" << std::endl;
    std::cout << "************* RESULTS ****************" << std::endl;
    std::cout << "**************************************" << std::endl;
    std::cout << "Algorithm: " << alg << std::endl;
    std::cout << "Total Processes: " << stats.num_process << std::endl;
    std::cout << "Total CPU Time: " << stats.total_cpu << std::endl;
    std::cout << "Total Work Units: " << stats.total_work_units << std::endl;
    std::cout << "CPU Time per work unit: " << stats.total_cpu / stats.total_work_units << std::endl;
    std::cout << "CPU Time per process: " << stats.total_cpu / stats.num_process << std::endl;
    std::cout << "**************************************" << std::endl;
}

int main()
{
    auto queue = makeQueue<Process>();

    uint64_t seconds = Utils::getTimeStamp();
    uint64_t stopTS = Utils::getTimeStamp() + (EXECUTION_TIME_SECONDS * MILLISECONS_IN_A_SECOND);

    auto t1 = Utils::Time();

    auto algorithm = bindSimulator(EAlgorithms::FCFS);

    auto pg = ProcessGenerator::createGenerator(queue);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    algorithm.Simulate(queue);

    while (seconds <= stopTS)
    {
        seconds = Utils::getTimeStamp();
    }
    
    algorithm.Stop();
    pg->Stop();

    auto t2 = Utils::Time();

    ShowStats(algorithm.getStats(), "FCFS");

    std::cout << "Executing stuff for " << Utils::Diff(t1, t2) / MICROSECONS_IN_A_SECOND << " seconds" << std::endl;

    return 0;
}
