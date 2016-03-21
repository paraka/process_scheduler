#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../src/Queue.h"
#include "../src/Process.h"
#include "../src/AlgorithmSimulator.h"
#include "../src/Stats.h"

using QueuePtr = std::shared_ptr<Queue<Process>>;

class Foo
{
public:
    static void Algorithm(QueuePtr queue, Stats& stats)
    {
        stats.total_work_units = 40;
        stats.total_cpu= 110.3;
        stats.num_process = 1000;
    }
};

class AlgorithmSimulatorTests : public ::testing::Test
{

protected:
    AlgorithmSimulatorTests()
    {
        queue_ = makeQueue<Process>();
    }

    virtual void SetUp() 
    {
    }

    virtual void TearDown() {}

protected:
    QueuePtr queue_;
};

TEST_F(AlgorithmSimulatorTests, BindCorrectly)
{
     AlgorithmSimulator alg(std::bind(&Foo::Algorithm, std::placeholders::_1, std::placeholders::_2));
     alg.Simulate(queue_);
     alg.Stop();
     ASSERT_EQ(alg.getStats().total_work_units, 40);
     ASSERT_EQ(alg.getStats().total_cpu, 110.3);
     ASSERT_EQ(alg.getStats().num_process, 1000);
}
