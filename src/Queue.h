#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <deque>
#include <mutex>
#include <algorithm>

enum class PopCriteria
{
    PRIORITY = 0,
    ARRIVAL_TIME,
};

template <typename T>
class Queue
{
public:
    Queue() = default;
    ~Queue() = default;
    Queue& operator=(const Queue&) = delete;
    Queue(const Queue& other) = delete;

    using ContainerType = std::deque<T>;
    using iterator = typename ContainerType::iterator;

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return queue_.empty();
    }

    unsigned size() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return queue_.size();
    }

    void push(T item)
    {
        std::lock_guard<std::mutex> lock(m_);
        queue_.push_back(item);
    }

    auto pop(PopCriteria c)
    {
        std::lock_guard<std::mutex> lock(m_);
        if (queue_.empty()) throw std::logic_error("Empty queue");

        iterator ret;

        if (c == PopCriteria::PRIORITY) 
        {
            auto comp1 = [](const T &a, const T &b ) { return a.getPriority() < b.getPriority(); }; 
            ret = std::max_element(queue_.begin(), queue_.end(), comp1);
        }
        else
        {
            auto comp1 = [](const T &a, const T &b ) { return a.getTimeStamp() < b.getTimeStamp(); };
            ret = std::min_element(queue_.begin(), queue_.end(), comp1);
        }

        queue_.erase(queue_.begin() + std::distance(queue_.begin(), ret));

        return ret;
    }

    void debug()
    {
        for (auto &el : queue_)
        {
            el.debugProcess();
        }
    }

private:
    std::deque<T> queue_;
    mutable std::mutex m_;
};

#endif
