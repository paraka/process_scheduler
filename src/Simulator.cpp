#include <boost/program_options.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include "Queue.h"
#include "Process.h"
#include "Utils.h"
#include "AlgorithmSimulator.h"
#include "ProcessGenerator.h"
#include "Algorithms.h"

namespace
{
    const int OK = 0;
    const int HELP = 1;
    const int ERROR = 2;
    const int EXCEPTION = 3;
    static const uint32_t MILLISECONS_IN_A_SECOND = 1000;
    static const uint32_t MICROSECONS_IN_A_SECOND = 1000000;
} // namespace

using ConfigMap = std::map<std::string, boost::variant<std::string, uint64_t>>;

static int ParseCmdLine(int argc, char *argv[], ConfigMap & cmap)
{
    try
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Print help message")
            ("simulation_seconds,t", po::value<uint64_t>()->required(), "Simulation time (seconds)")
            ("algorithm,a", po::value<std::string>()->required(), "Algorithm to use in simulation (fcfs, rr, pq, sjk)");

        po::variables_map vm;

        try
        {
            po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

            if (vm.count("help"))
            {
                std::cout << "Parameters: " << std::endl
                                            << desc << std::endl;
                return HELP;
            }

            if (vm.count("simulation_seconds"))
            {
                cmap["sim_time"] = vm["simulation_seconds"].as<uint64_t>();
            }

            if (vm.count("algorithm"))
            {
                std::string opt(vm["algorithm"].as<std::string>());
                std::transform(opt.begin(), opt.end(), opt.begin(), ::toupper);
                cmap["algorithm"] = opt;
            }

            po::notify(vm);
        } 
        catch (const po::error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return ::ERROR;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return ::EXCEPTION;
    }

    return OK;
}

static auto bindSimulator(EAlgorithms algorithm)
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
                AlgorithmSimulator sjk(std::bind(&Algorithms::SJK, std::placeholders::_1, std::placeholders::_2));
                return sjk;
            }
        default:
            throw std::logic_error("Invalid algorithm...");
    }
}

static EAlgorithms getAlgorithmByString(const std::string &algorithm)
{
    if (algorithm == "FCFS")
        return EAlgorithms::FCFS;
    else if (algorithm == "RR")
        return EAlgorithms::RR;
    else if (algorithm == "PQ")
        return EAlgorithms::PQ;
    else if (algorithm == "SJK")
        return EAlgorithms::SJK;
    else
        throw std::logic_error("No valid algorithm");
}

static void ShowStats(const Stats &stats, const std::string &alg)
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

int main(int argc, char *argv[])
{
    ConfigMap cmap;

    if (ParseCmdLine(argc, argv, cmap) != OK)
    {
        exit(0);
    }

    auto queue = makeQueue<Process>();

    uint64_t seconds = Utils::getTimeStamp();
    uint64_t stopTS = Utils::getTimeStamp() + (boost::get<uint64_t>(cmap["sim_time"]) * MILLISECONS_IN_A_SECOND);

    auto t1 = Utils::Time();

    auto algorithm = bindSimulator(getAlgorithmByString(boost::get<std::string>(cmap["algorithm"])));

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

    ShowStats(algorithm.getStats(), boost::get<std::string>(cmap["algorithm"]));

    std::cout << "Executing stuff for " << Utils::Diff(t1, t2) / MICROSECONS_IN_A_SECOND << " seconds" << std::endl;

    return 0;
}
