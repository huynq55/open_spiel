#ifndef OPEN_SPIEL_GAMES_IMPL_COMMON_XIANGQI_COMMON_H_
#define OPEN_SPIEL_GAMES_IMPL_COMMON_XIANGQI_COMMON_H_

#include <cstdint>
#include <string>

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

}  // namespace xiangqi_common
}  // namespace open_spiel
#endif