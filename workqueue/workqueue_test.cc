#include "workqueue/workqueue.h"

#include <vector>

#include "gtest/gtest.h"

namespace workqueue {
namespace {

class SummationWorkItem : public WorkItem {
  public:
    explicit SummationWorkItem(int64_t n) : n_(n), result_(0) {}

    void Run() {
      for (int64_t i = 0; i <= n_; i++) {
        result_ += i;
      }
    }

    int64_t Result() { return result_; }

  private:
    int64_t n_;
    int64_t result_ = 0;
};

TEST(WorkQueueTests, WorkList) {
  std::vector<std::shared_ptr<SummationWorkItem>> items {
    std::make_shared<SummationWorkItem>(10),
    std::make_shared<SummationWorkItem>(100000),
  };

  WorkQueue queue;
  for (auto& item : items) {
    queue.Enqueue(item);
  }

  items[0]->WaitForFinish();
  EXPECT_EQ(items[0]->Result(), 55);

  items[1]->WaitForFinish();
  EXPECT_EQ(items[1]->Result(), 5000050000);
}

}

}