#pragma once

#include <functional>
#include <string>
#include <utility>

#include "st/endings/EndingType.hpp"

namespace st {

class Player;

class FinalChoice {
 public:
  using Availability = std::function<bool(const Player&)>;
  using Execution = std::function<EndingType(Player&)>;

  FinalChoice(std::string text, Availability availability, Execution execution)
      : text_(std::move(text)),
        availability_(std::move(availability)),
        execution_(std::move(execution)) {}

  [[nodiscard]] const std::string& text() const noexcept { return text_; }
  [[nodiscard]] bool isAvailable(const Player& player) const {
    return availability_(player);
  }
  [[nodiscard]] EndingType execute(Player& player) const {
    return execution_(player);
  }

 private:
  std::string text_;
  Availability availability_;
  Execution execution_;
};

}  // namespace st
