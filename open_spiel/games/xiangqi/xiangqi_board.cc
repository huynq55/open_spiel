#include "open_spiel/games/xiangqi/xiangqi_board.h"

#include "open_spiel/abseil-cpp/absl/strings/str_cat.h"
#include "open_spiel/spiel_utils.h"

namespace open_spiel {
namespace xiangqi {

std::string ColorToString(Color c) {
  switch (c) {
    case Color::kBlack:
      return "black";
    case Color::kWhite:
      return "white";
    case Color::kEmpty:
      return "empty";
    default:
      SpielFatalError(absl::StrCat("Unknown color: ", c));
      return "This will never return.";
  }
}

absl::optional<PieceType> PieceTypeFromChar(char c) {
  switch (toupper(c)) {
    case 'P':
      return PieceType::kSoldier;
    case 'C':
      return PieceType::kCannon;
    case 'N':
      return PieceType::kHorse;
    case 'B':
      return PieceType::kElephant;
    case 'R':
      return PieceType::kChariot;
    case 'A':
      return PieceType::kAdvisor;
    case 'K':
      return PieceType::kGeneral;
    default:
      std::cerr << "Invalid piece type: " << c << std::endl;
      return absl::nullopt;
  }
}

}  // namespace xiangqi
}  // namespace open_spiel