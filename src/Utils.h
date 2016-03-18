#ifndef _UTILS_H_
#define _UTILS_H_

#include <random>
#include <chrono>

using namespace std::chrono;

class Utils
{
public:
    // T must be RealType
    template <typename T>
    static auto getRandom(T min, T max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<T> dist(min, max);
        return dist(mt);
    }

    static auto getTimeStamp()
    {
        return (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    }

    static auto Time()
    {
        return (high_resolution_clock::now());
    }

    static auto Diff(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2)
    {
        return (duration_cast<microseconds>(t2 - t1).count());
    }
};

#endif // _UTILS_H_
