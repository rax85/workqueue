#include "workqueue.h"

#include <algorithm>
#include <cassert>

namespace workqueue {

void WorkItem::Finish() {
  std::unique_lock lock(done_mutex_);
  done_ = true;
  done_cond_var_.notify_all();
}

void WorkItem::WaitForFinish() {
  std::unique_lock lock(done_mutex_);
  done_cond_var_.wait(lock, [this] { return this->done_; });
}

WorkQueue::WorkQueue(size_t num_threads) {
  if (num_threads == 0) {
    num_threads = std::thread::hardware_concurrency();
    num_threads = std::max(num_threads, 4UL);
  }

  for (size_t i = 0; i < num_threads; i++) {
    workers_.emplace_back(&WorkQueue::WorkLoop, this);
  }
}

void WorkQueue::Terminate() {
  {
    std::unique_lock lock(work_mutex_);
    terminate_ = true;
    work_available_.notify_all();
  }

  for (auto& worker : workers_) {
    worker.join();
  }
}

WorkQueue::~WorkQueue() {
  Terminate();
  workers_.clear();
}

void WorkQueue::Enqueue(std::shared_ptr<WorkItem> work_item) {
  std::unique_lock lock(work_mutex_);
  work_.push_back(work_item);
  work_available_.notify_all();
}

void WorkQueue::WorkLoop() {
  while (!terminate_) {
    std::shared_ptr<WorkItem> work_item = nullptr;
    {
      std::unique_lock lock(work_mutex_);
      work_available_.wait(lock, [this] { return this->terminate_ == true || !work_.empty(); });

      if (work_.empty()) {
        continue;
      }
      work_item = work_.front();
      work_.pop_front();
    }

    assert (work_item != nullptr);
    work_item->Run();
    work_item->Finish();
  }
}

}