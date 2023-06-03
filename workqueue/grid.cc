#include "workqueue/grid.h"

namespace workqueue::internal {

std::optional<int64_t> Offset2d(int64_t x_dim, int64_t y_dim, int64_t x, int64_t y) {
  if ((x < 0 || x >= x_dim) || (y < 0 || y >= y_dim)) {
    return std::nullopt;
  }
  return x * y_dim + y;
}

std::optional<int64_t> Offset3d(int64_t x_dim, int64_t y_dim, int64_t z_dim, int64_t x, int64_t y, int64_t z) {
  if ((x < 0 || x >= x_dim) || (y < 0 || y >= y_dim) || (z < 0 || z >= z_dim)) {
    return std::nullopt;
  }
  return x * y_dim * z_dim + y * z_dim + z;
}

std::array<std::optional<int64_t>, 9> OffsetsD2Q9(int64_t x_dim, int64_t y_dim, int64_t x, int64_t y) {
  //          6  2  5 (1, 1)
  //          3  0  1
  // (-1, -1) 7  4  8
  return {
    Offset2d(x_dim, y_dim, x,     y),
    Offset2d(x_dim, y_dim, x + 1, y),
    Offset2d(x_dim, y_dim, x,     y + 1),
    Offset2d(x_dim, y_dim, x - 1, y),
    Offset2d(x_dim, y_dim, x,     y - 1),
    Offset2d(x_dim, y_dim, x + 1, y + 1),
    Offset2d(x_dim, y_dim, x - 1, y + 1),
    Offset2d(x_dim, y_dim, x - 1, y - 1),
    Offset2d(x_dim, y_dim, x + 1, y - 1),
  };
}

}