#include <gtest/gtest.h>
#include "../src/Queue.h"
#include "../src/Process.h"

class QueueFixture : public ::testing::Test
{
private:
    void add_initial_stuff()
    {
        Process p1(1,10.5);
        Process p2(2,1.6);
        Process p3(6,20.5);
        Process p4(7,6.6);
        p3.setPriority(10);
        p4.setPriority(20);
        p1.setTimeStamp(123);
        p2.setTimeStamp(124);
        p3.setTimeStamp(121);
        p4.setTimeStamp(128);

        queue_->push(p1);
        queue_->push(p2);
        queue_->push(p3);
        queue_->push(p4);
    }

protected:
    QueueFixture()
    {
        queue_ = makeQueue<Process>();
    }

    void CleanQueue()
    {
        queue_->clear();
    }

    virtual void SetUp() 
    {
        add_initial_stuff();
        ASSERT_EQ(queue_->size(), 4);
    }

    virtual void TearDown() {}

protected:
    using QueuePtr = std::shared_ptr<Queue<Process>>;
    QueuePtr queue_;
};

TEST_F(QueueFixture, PopGetCorrectCriteriaElement)
{
    auto comp = [](const Process &a, const Process &b ) { return a.getPriority() > b.getPriority(); };
    auto ret = queue_->pop(comp);
    ASSERT_EQ((*ret).getPriority(), 20);
    ASSERT_EQ((*ret).getPid(), 7);
    ASSERT_EQ(queue_->size(), 3);
    auto comp2 = [](const Process &a, const Process &b ) { return a.getTimeStamp() < b.getTimeStamp(); };
    ret = queue_->pop(comp2);
    ASSERT_EQ((*ret).getTimeStamp(), 121);
    ASSERT_EQ((*ret).getPid(), 6);
    ASSERT_EQ(queue_->size(), 2);
}

TEST_F(QueueFixture, EmptyQueueThrowsOnPop)
{
    CleanQueue();
    auto comp = [](const Process &a, const Process &b ) { return a.getTimeStamp() < b.getTimeStamp(); };
    ASSERT_THROW(queue_->pop(comp), std::logic_error);
}
