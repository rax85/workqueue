#include "workqueue/grid.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace workqueue {
namespace {

class TestGrid2d : public Grid2d<int> {
  public:
    TestGrid2d() : Grid2d<int>(3, 3) {
      //        2  5  8 (2, 2)
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

class TestGrid3d : public Grid3d<int> {
  public:
    TestGrid3d() : Grid3d<int>(3, 3, 3) {
      //           2  5  8 (2, 2, 0)            11  14  17 (2, 2, 1)             20  23  26 (2, 2, 2)
      //           1  4  7                      10  13  16                       19  22  25
      // (0, 0, 0) 0  3  6            (0, 0, 1) 9   12  15             (0, 0, 2) 18  21  24
      int ctr = 0;
      for (int z = 0; z < 3; z++) {
        for (int x = 0; x < 3; x++) {
          for (int y = 0; y < 3; y++) {
            *At(x, y, z) = ctr;
            ctr++;
          }
        }
      }
    }
};

TEST(GridTests, Get3dInBounds) {
  TestGrid3d grid;
  EXPECT_EQ(*grid.At(0, 0, 0), 0);
  EXPECT_EQ(*grid.At(2, 2, 2), 26);
  EXPECT_EQ(*grid.At(1, 1, 1), 13);
}

TEST(GridTests, Get3dOutOfBounds) {
  TestGrid3d grid;
  EXPECT_EQ(grid.At(3, 0, 0), nullptr);
  EXPECT_EQ(grid.At(2, 3, 2), nullptr);
  EXPECT_EQ(grid.At(1, 1, 3), nullptr);
  EXPECT_EQ(grid.At(-1, 0, 0), nullptr);
  EXPECT_EQ(grid.At(2, -1, 2), nullptr);
  EXPECT_EQ(grid.At(1, 1, -1), nullptr);
}

TEST(GridTests, D3Q27InBounds) {
  TestGrid3d grid;
  auto d3q27 = grid.D3Q27(1, 1, 1);
  std::vector<int> observed;
  for (int i = 0; i < 27; i++) {
    observed.push_back(*d3q27[i]);
  }
  EXPECT_THAT(observed, testing::ElementsAreArray({
    13, // 0
    16, // 1
    10, // 2
    22, // 3
    4,  // 4
    14, // 5
    12, // 6
    25, // 7
    19, // 8
    7,  // 9
    1,  // 10
    17, // 11
    11, // 12
    15, // 13
    9,  // 14
    23, // 15
    5,  // 16
    21, // 17
    3,  // 18
    26, // 19
    20, // 20
    8,  // 21
    2,  // 22
    24, // 23
    18, // 24
    6,  // 25
    0   // 27
  }));
}

}
}
