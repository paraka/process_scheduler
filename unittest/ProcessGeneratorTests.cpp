#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../src/Queue.h"
#include "../src/Process.h"
#include "../src/ProcessGenerator.h"

class ProcessGeneratorTests : public ::testing::Test
{

protected:
    ProcessGeneratorTests()
    {
        queue_ = makeQueue<Process>();
    }

    virtual void SetUp() 
    {
        pgPtr = ProcessGenerator::createGenerator(queue_); 
    }

    virtual void TearDown() {}

protected:
    using QueuePtr = std::shared_ptr<Queue<Process>>;
    QueuePtr queue_;
    ProcessGeneratorPtr pgPtr;
};

TEST_F(ProcessGeneratorTests, ThreadEnqueueCorrectly)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pgPtr->Stop();
    ASSERT_NE(queue_->size(), 0);
}
