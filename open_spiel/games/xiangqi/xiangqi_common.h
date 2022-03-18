#ifndef OPEN_SPIEL_GAMES_IMPL_COMMON_XIANGQI_COMMON_H_
#define OPEN_SPIEL_GAMES_IMPL_COMMON_XIANGQI_COMMON_H_

#include <cstdint>
#include <random>
#include <string>

#include "open_spiel/abseil-cpp/absl/random/uniform_int_distribution.h"

namespace open_spiel {
namespace xiangqi_common {
struct Offset {
  int8_t x_offset;
  int8_t y_offset;

  bool operator==(const Offset& other) const {
    return x_offset == other.x_offset && y_offset == other.y_offset;
  }
};

// x corresponds to file (column / letter)
// y corresponds to rank (row / number).
struct Square {
  Square& operator+=(const Offset& offset) {
    x += offset.x_offset;
    y += offset.y_offset;
    return *this;
  }

  bool operator==(const Square& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Square& other) const { return !(*this == other); }

  int8_t x;
  int8_t y;
};

constexpr Square kInvalidSquare{-1, -1};

inline std::string SquareToString(const Square& square) {
  if (square == kInvalidSquare)
    return "None";
  else {
    std::string s;
    s.push_back('a' + square.x);
    s.push_back('0' + square.y);
    return s;
  }
}

// n-dimensional array of uniform random numbers.
// Example:
//   ZobristTable<int, 3, 4, 5> table;
//
//   table[a][b][c] is a random int where a < 3, b < 4, c < 5
//
template <typename T, std::size_t InnerDim, std::size_t... OtherDims>
class ZobristTable {
 public:
  using Generator = std::mt19937_64;
  using NestedTable = ZobristTable<T, OtherDims...>;

  ZobristTable(Generator::result_type seed) {
    Generator generator(seed);
    absl::uniform_int_distribution<Generator::result_type> dist;
    data_.reserve(InnerDim);
    for (std::size_t i = 0; i < InnerDim; ++i) {
      data_.emplace_back(dist(generator));
    }
  }

  const NestedTable& operator[](std::size_t inner_index) const {
    return data_[inner_index];
  }

 private:
  std::vector<NestedTable> data_;
};

// 1-dimensional array of uniform random numbers.
template <typename T, std::size_t InnerDim>
class ZobristTable<T, InnerDim> {
 public:
  using Generator = std::mt19937_64;

  ZobristTable(Generator::result_type seed) : data_(InnerDim) {
    Generator generator(seed);
    absl::uniform_int_distribution<T> dist;
    for (auto& field : data_) {
      field = dist(generator);
    }
  }

  T operator[](std::size_t index) const { return data_[index]; }

 private:
  std::vector<T> data_;
};

}  // namespace xiangqi_common
}  // namespace open_spiel
#endif