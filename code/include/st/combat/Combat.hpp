#pragma once

#include <memory>
#include <vector>

#include "st/combat/CombatAction.hpp"
#include "st/combat/Enemy.hpp"

namespace st {

class Player;
class Random;
class ConsoleView;

enum class CombatResult { Victory, AwarenessCollapse, ThreadBreak };

class Combat {
 public:
  Combat(Player& player, std::unique_ptr<Enemy> enemy, ConsoleView& view,
         Random& random);

  [[nodiscard]] CombatResult run();

 private:
  Player& player_;
  std::unique_ptr<Enemy> enemy_;
  ConsoleView& view_;
  Random& random_;
  std::vector<std::unique_ptr<CombatAction>> actions_;
};

}  // namespace st
