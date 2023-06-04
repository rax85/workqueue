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

std::array<std::optional<int64_t>, 27> OffsetsD3Q27(int64_t x_dim, int64_t y_dim, int64_t z_dim, int64_t x, int64_t y, int z) {
  return {
    // Uses a rigth handed coordinate system (aka +z comes out of the screen).
    // https://en.wikipedia.org/wiki/Octant_(solid_geometry)
    // https://lbm-lattice-models.vercel.app/
    // D3Q7: https://lbm-lattice-models.vercel.app/d3q6.html
    Offset3d(x_dim, y_dim, z_dim, x,     y,     z),     // 0
    Offset3d(x_dim, y_dim, z_dim, x + 1, y,     z),     // 1
    Offset3d(x_dim, y_dim, z_dim, x - 1, y,     z),     // 2
    Offset3d(x_dim, y_dim, z_dim, x,     y,     z + 1), // 3
    Offset3d(x_dim, y_dim, z_dim, x,     y,     z - 1), // 4
    Offset3d(x_dim, y_dim, z_dim, x,     y + 1, z),     // 5
    Offset3d(x_dim, y_dim, z_dim, x,     y - 1, z),     // 6
    // D3Q19 https://lbm-lattice-models.vercel.app/d3q19.html
    Offset3d(x_dim, y_dim, z_dim, x + 1, y,     z + 1), // 7
    Offset3d(x_dim, y_dim, z_dim, x - 1, y,     z + 1), // 8
    Offset3d(x_dim, y_dim, z_dim, x + 1, y,     z - 1), // 9
    Offset3d(x_dim, y_dim, z_dim, x - 1, y,     z - 1), // 10
    Offset3d(x_dim, y_dim, z_dim, x + 1, y + 1, z),     // 11
    Offset3d(x_dim, y_dim, z_dim, x - 1, y + 1, z),     // 12
    Offset3d(x_dim, y_dim, z_dim, x + 1, y - 1, z),     // 13
    Offset3d(x_dim, y_dim, z_dim, x - 1, y - 1, z),     // 14
    Offset3d(x_dim, y_dim, z_dim, x,     y + 1, z + 1), // 15
    Offset3d(x_dim, y_dim, z_dim, x,     y + 1, z - 1), // 16
    Offset3d(x_dim, y_dim, z_dim, x,     y - 1, z + 1), // 17
    Offset3d(x_dim, y_dim, z_dim, x,     y - 1, z - 1), // 18
    // D3Q27 https://lbm-lattice-models.vercel.app/d3q27.html
    Offset3d(x_dim, y_dim, z_dim, x + 1, y + 1, z + 1), // 19
    Offset3d(x_dim, y_dim, z_dim, x - 1, y + 1, z + 1), // 20
    Offset3d(x_dim, y_dim, z_dim, x + 1, y + 1, z - 1), // 21
    Offset3d(x_dim, y_dim, z_dim, x - 1, y + 1, z - 1), // 22
    Offset3d(x_dim, y_dim, z_dim, x + 1, y - 1, z + 1), // 23
    Offset3d(x_dim, y_dim, z_dim, x - 1, y - 1, z + 1), // 24
    Offset3d(x_dim, y_dim, z_dim, x + 1, y - 1, z - 1), // 25
    Offset3d(x_dim, y_dim, z_dim, x - 1, y - 1, z - 1), // 26
  };
}


}