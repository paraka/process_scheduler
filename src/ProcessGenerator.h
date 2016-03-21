#ifndef _PROCESS_GENERATOR_H_
#define _PROCESS_GENERATOR_H_

#include <thread>
#include <memory>

template <typename T> class Queue;
class Process;

using QueuePtr = std::shared_ptr<Queue<Process>>;

class ProcessGenerator;
using ProcessGeneratorPtr = std::unique_ptr<ProcessGenerator>;

class ProcessGenerator
{
public:
    virtual ~ProcessGenerator();

    void Stop() { end_ = true; }
     
    // Factory: safe construction & thread start
    static ProcessGeneratorPtr createGenerator(QueuePtr q); 

private:
    ProcessGenerator(const ProcessGenerator&) = delete;
    ProcessGenerator& operator=(const ProcessGenerator&) = delete;

    ProcessGenerator(QueuePtr q) : queue_(q), end_(false) {}

    void run(); 

private: 
    QueuePtr queue_;
    std::thread th_;
    bool end_;
};

#endif // _PROCESS_GENERATOR_H_
