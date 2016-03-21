#include <gtest/gtest.h>
#include <thread>
#include "../src/Utils.h"

TEST(Utils, RandomValue)
{
    auto random = Utils::getRandom<double>(1.0, 5.0);
    ASSERT_GE(random, 1.0);
    ASSERT_LE(random, 5.0);
}

TEST(Utils, GetTimeStampWorks)
{
    auto ts1 = Utils::getTimeStamp();
    std::this_thread::sleep_for(1s);
    auto ts2 = Utils::getTimeStamp();
    ASSERT_GE(ts2 - ts1, 1);
}

TEST(Utils, DiffWorks)
{
    auto ts1 = Utils::Time();
    std::this_thread::sleep_for(1s);
    auto ts2 = Utils::Time();
    ASSERT_GE(Utils::Diff(ts1,ts2), 1000000);
}

