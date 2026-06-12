#pragma once

#include <string>
#include <utility>

#include "st/core/Player.hpp"

namespace st {

class GameState {
 public:
  GameState(Player playerSnapshot, std::string nodeId)
      : player_(std::move(playerSnapshot)), nodeId_(std::move(nodeId)) {}

  [[nodiscard]] const Player& player() const noexcept { return player_; }
  [[nodiscard]] const std::string& nodeId() const noexcept { return nodeId_; }

 private:
  Player player_;
  std::string nodeId_;
};

}  // namespace st
