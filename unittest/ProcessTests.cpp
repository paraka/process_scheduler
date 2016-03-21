#include <gtest/gtest.h>
#include "../src/Process.h"
#include "../src/Utils.h"

class ProcessF: public ::testing::Test
{
protected:
    ProcessF(): process_(1,20)
    {
        process_.setPriority(15);
    }

    virtual void SetUp() {}

    virtual void TearDown() {}

protected:
    Process process_;
};

TEST_F(ProcessF, ProcessFillsCorrectly)
{
    ASSERT_EQ(process_.getPid(), 1);
    ASSERT_EQ(process_.getCPUPercent(), 20);
    ASSERT_EQ(process_.getPriority(), 15);
    ASSERT_NE(process_.getPriority(), -1);
    auto random = Utils::getRandom<double>(1, 1);
    auto ts = Utils::getTimeStamp() + static_cast<uint64_t>(random);
    ASSERT_GE(process_.getTimeStamp(), ts);
    ASSERT_NE(process_.getTimeStamp(), 0);
}
