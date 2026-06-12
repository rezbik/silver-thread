#pragma once

#include <string>

namespace st {

class Player;
class Enemy;
class Random;

class CombatAction {
 public:
  virtual ~CombatAction() = default;
  [[nodiscard]] virtual const std::string& name() const noexcept = 0;
  [[nodiscard]] virtual bool isAvailable(const Player& player) const {
    (void)player;
    return true;
  }
  virtual std::string execute(Player& player, Enemy& enemy, Random& random) = 0;
};

}  // namespace st
