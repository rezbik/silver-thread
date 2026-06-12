#pragma once

#include <string>

namespace st {

/// 6 концовок
enum class EndingType {
  Replacement,
  Denial,
  TrueMerge,
  IncompleteMerge,
  Absorption,
  ThreadBreak
};

/// идентификаторы узлов концовок
[[nodiscard]] inline std::string endingNodeId(EndingType type) {
  switch (type) {
    case EndingType::Replacement:
      return "ending_a";
    case EndingType::Denial:
      return "ending_b";
    case EndingType::TrueMerge:
      return "ending_v";
    case EndingType::IncompleteMerge:
      return "ending_v2";
    case EndingType::Absorption:
      return "ending_g";
    case EndingType::ThreadBreak:
      return "ending_d";
  }
  return "ending_d";
}

}  // namespace st
