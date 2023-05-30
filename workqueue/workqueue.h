#pragma once

#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace workqueue {

class WorkItem {
  public:
    virtual void Run() {}

    void Finish();
    void WaitForFinish();

  private:
    bool done_ = false;
    std::mutex done_mutex_;
    std::condition_variable done_cond_var_;
};


class WorkQueue {
  public:
    WorkQueue(size_t num_threads = 0);
    ~WorkQueue();

    void Enqueue(std::shared_ptr<WorkItem> work);

    void Terminate();

  private:
    void WorkLoop();

    std::vector<std::thread> workers_;
    std::deque<std::shared_ptr<WorkItem>> work_;
    std::mutex work_mutex_;
    std::condition_variable work_available_;
    std::atomic_bool terminate_ = false;
};

}