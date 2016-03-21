#ifndef _PROCESS_H_
#define _PROCESS_H_

class Process
{
public:
    Process(uint32_t pid, double cpu_percent);

    uint32_t getPid() const { return pid_; }
    uint64_t getTimeStamp() const { return timestamp_; }
    double getCPUPercent() const { return cpu_percent_; }
    int32_t getPriority() const { return priority_; }
    void setPriority(int32_t priority) { priority_ = priority; }
    uint32_t getWorkUnits() const { return work_units_; }
    void setWorkUnits(uint32_t wu) { work_units_ = wu; }
    // For testing purpose
    void setTimeStamp(int64_t ts) { timestamp_ = ts; }
    void debugProcess();

private:
    uint32_t pid_;
    uint64_t timestamp_; 
    double cpu_percent_;
    uint32_t work_units_;
    int32_t priority_;
};

#endif // _PROCESS_H_ 
