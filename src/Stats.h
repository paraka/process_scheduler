#ifndef STATS_H_
#define STATS_H_

struct Stats
{
    uint64_t num_process;
    double total_cpu;
    uint32_t total_work_units;

    Stats() : num_process(0), total_cpu(0.0) {}
};

#endif // STATS_H_

