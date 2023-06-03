#include "workqueue/grid.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace workqueue {
namespace {

class TestGrid2d : public Grid2d<int> {
  public:
    TestGrid2d() : Grid2d<int>(3, 3) {
      //        2  5  8
      //        1  4  7
      // (0, 0) 0  3  6
      elements_ = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    }
};

TEST(GridTests, SetAndGet2d) {
  TestGrid2d grid;
  EXPECT_EQ(*grid.At(2, 2), 8);
  EXPECT_EQ(*grid.At(0, 0), 0);
  EXPECT_EQ(*grid.At(1, 1), 4);
  *grid.At(1, 1) = 7;
  EXPECT_EQ(*grid.At(1, 1), 7);
}

TEST(GridTests, OutOfBounds2d) {
  TestGrid2d grid;
  EXPECT_EQ(grid.At(-1, 0), nullptr);
  EXPECT_EQ(grid.At(3, 3), nullptr);
}

TEST(GridTests, D2Q9InBounds) {
  TestGrid2d grid;
  auto d2q9 = grid.D2Q9(1, 1);
  EXPECT_EQ(*d2q9[0], 4);
  EXPECT_EQ(*d2q9[1], 7);
  EXPECT_EQ(*d2q9[2], 5);
  EXPECT_EQ(*d2q9[3], 1);
  EXPECT_EQ(*d2q9[4], 3);
  EXPECT_EQ(*d2q9[5], 8);
  EXPECT_EQ(*d2q9[6], 2);
  EXPECT_EQ(*d2q9[7], 0);
  EXPECT_EQ(*d2q9[8], 6);
}

TEST(GridTests, D2Q9Boundary) {
  TestGrid2d grid;
  EXPECT_THAT(grid.D2Q9(2, 2), testing::ElementsAre(grid.At(2, 2), nullptr, nullptr, grid.At(1, 2), grid.At(2, 1), nullptr, nullptr, grid.At(1, 1), nullptr));
}

}
}
