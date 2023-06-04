#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace workqueue {
namespace internal {

std::optional<int64_t> Offset2d(int64_t x_dim, int64_t y_dim, int64_t x, int64_t y);
std::optional<int64_t> Offset3d(int64_t x_dim, int64_t y_dim, int64_t z_dim, int64_t x, int64_t y, int64_t z);

std::array<std::optional<int64_t>, 9> OffsetsD2Q9(int64_t x_dim, int64_t y_dim, int64_t x, int64_t y);
std::array<std::optional<int64_t>, 27> OffsetsD3Q27(int64_t x_dim, int64_t y_dim, int64_t z_dim, int64_t x, int64_t y, int z);

}

template <class Element>
class Grid2d {
  public:
    Grid2d() = default;
    Grid2d(int64_t x_dim, int64_t y_dim) : x_dim_(x_dim), y_dim_(y_dim), elements_(x_dim * y_dim) {}

    const Element* At(int64_t x, int64_t y) const {
      auto offset = internal::Offset2d(x_dim_, y_dim_, x, y);
      if (offset.has_value()) {
        return &elements_[offset.value()];
      }
      return nullptr;
    }

    Element* At(int64_t x, int64_t y) {
      auto offset = internal::Offset2d(x_dim_, y_dim_, x, y);
      if (offset.has_value()) {
        return &elements_[offset.value()];
      }
      return nullptr;
    }

    std::array<Element*, 9> D2Q9(int64_t x, int64_t y) {
      std::array<Element*, 9> values;
      auto offsets = internal::OffsetsD2Q9(x_dim_, y_dim_, x, y);
      for (int i = 0; i < 9; i++) {
        if (offsets[i].has_value()) {
          values[i] = &elements_[offsets[i].value()];
        } else {
          values[i] = nullptr;
        }
      }
      return values;
    }

  protected:
    int64_t x_dim_ = 0;
    int64_t y_dim_ = 0;
    std::vector<Element> elements_;
};


template <class Element>
class Grid3d {
  public:
    Grid3d() = default;
    Grid3d(int64_t x_dim, int64_t y_dim, int64_t z_dim) : x_dim_(x_dim), y_dim_(y_dim), z_dim_(z_dim), elements_(x_dim * y_dim * z_dim) {}

    const Element* At(int64_t x, int64_t y, int64_t z) const {
      auto offset = internal::Offset3d(x_dim_, y_dim_, z_dim_, x, y, z);
      if (offset.has_value()) {
        return &elements_[offset.value()];
      }
      return nullptr;
    }

    Element* At(int64_t x, int64_t y, int64_t z) {
      auto offset = internal::Offset3d(x_dim_, y_dim_, z_dim_, x, y, z);
      if (offset.has_value()) {
        return &elements_[offset.value()];
      }
      return nullptr;
    }

    std::array<Element*, 27> D3Q27(int64_t x, int64_t y, int64_t z) {
      std::array<Element*, 27> values;
      auto offsets = internal::OffsetsD3Q27(x_dim_, y_dim_, z_dim_, x, y, z);
      for (int i = 0; i < 27; i++) {
        if (offsets[i].has_value()) {
          values[i] = &elements_[offsets[i].value()];
        } else {
          values[i] = nullptr;
        }
      }
      return values;
    }

  protected:
    int64_t x_dim_ = 0;
    int64_t y_dim_ = 0;
    int64_t z_dim_ = 0;
    std::vector<Element> elements_;
};
}