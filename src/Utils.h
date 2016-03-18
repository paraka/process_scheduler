#ifndef _UTILS_H_
#define _UTILS_H_

#include <random>

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
};
#endif // _UTILS_H_
