#pragma once

#include <vector>

#include "st/endings/EndingType.hpp"
#include "st/endings/FinalChoice.hpp"

namespace st {

class Player;
class ConsoleView;
class Mimicry;

class FinalBattle {
 public:
  FinalBattle(Player& player, ConsoleView& view, const Mimicry& mimicry);

  [[nodiscard]] EndingType run();

 private:
  [[nodiscard]] std::vector<FinalChoice> buildFinalChoices(bool limited) const;
  [[nodiscard]] static bool trueMergeConditionsMet(const Player& player);

  Player& player_;
  ConsoleView& view_;
  const Mimicry& mimicry_;
};

}  // namespace st
