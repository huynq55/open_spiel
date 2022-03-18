#ifndef OPEN_SPIEL_GAMES_IMPL_XIANGQI_XIANGQI_BOARD_H_
#define OPEN_SPIEL_GAMES_IMPL_XIANGQI_XIANGQI_BOARD_H_

#include "open_spiel/games/xiangqi/xiangqi_common.h"

namespace open_spiel {
namespace xiangqi {
using xiangqi_common::kInvalidSquare;
using xiangqi_common::Offset;
using xiangqi_common::Square;
using xiangqi_common::SquareToString;

template <std::size_t... Dims>
using ZobristTableU64 = xiangqi_common::ZobristTable<uint64_t, Dims...>;

enum class Color : int8_t { kBlack = 0, kWhite = 1, kEmpty = 2 };

inline int ToInt(Color color) { return color == Color::kWhite ? 1 : 0; }

inline Color OppColor(Color color) {
  return color == Color::kWhite ? Color::kBlack : Color::kWhite;
}

std::string ColorToString(Color c);

inline std::ostream& operator<<(std::ostream& stream, Color c) {
  return stream << ColorToString(c);
}

enum class PieceType : int8_t {
  kEmpty = 0,
  kGeneral = 1,
  kChariot = 2,
  kCannon = 3,
  kHorse = 4,
  kElephant = 5,
  kAdvisor = 6,
  kSoldier = 7
};

static inline constexpr std::array<PieceType, 7> kPieceTypes = {
    {PieceType::kGeneral, PieceType::kChariot, PieceType::kCannon,
     PieceType::kHorse, PieceType::kElephant, PieceType::kAdvisor,
     PieceType::kSoldier}};

// Tries to parse piece type from char ('K', 'R', 'C', 'N', 'B', 'A', 'P').
// Case-insensitive.
absl::optional<PieceType> PieceTypeFromChar(char c);

}  // namespace xiangqi
}  // namespace open_spiel
#endif