#pragma once

#include <optional>
#include <string>
#include <vector>

#include "st/story/Effect.hpp"
#include "st/story/Requirement.hpp"

namespace st {

class Player;

class Choice {
 public:
  Choice(std::string text, std::string targetId)
      : text_(std::move(text)), targetId_(std::move(targetId)) {}

  Choice& require(Requirement requirement) {
    requirements_.push_back(std::move(requirement));
    return *this;
  }

  Choice& withEffect(Effect effect) {
    effect_ = std::move(effect);
    return *this;
  }

  Choice& parasitic() {
    parasitic_ = true;
    return *this;
  }
  Choice& whisper() {
    whisper_ = true;
    return *this;
  }

  Choice& onAwarenessZero(std::string targetId, Effect extra = {}) {
    awarenessZeroTarget_ = std::move(targetId);
    awarenessZeroEffect_ = std::move(extra);
    return *this;
  }

  [[nodiscard]] bool isAvailable(const Player& player) const {
    for (const auto& requirement : requirements_) {
      if (!requirement.check(player)) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] const std::string& text() const noexcept { return text_; }
  [[nodiscard]] const std::string& targetId() const noexcept {
    return targetId_;
  }
  [[nodiscard]] const std::optional<Effect>& effect() const noexcept {
    return effect_;
  }
  [[nodiscard]] bool isParasitic() const noexcept { return parasitic_; }
  [[nodiscard]] bool isWhisper() const noexcept { return whisper_; }
  [[nodiscard]] const std::optional<std::string>& awarenessZeroTarget()
      const noexcept {
    return awarenessZeroTarget_;
  }
  [[nodiscard]] const std::optional<Effect>& awarenessZeroEffect()
      const noexcept {
    return awarenessZeroEffect_;
  }

 private:
  std::string text_;
  std::string targetId_;
  std::vector<Requirement> requirements_;
  std::optional<Effect> effect_;
  bool parasitic_{false};
  bool whisper_{false};
  std::optional<std::string> awarenessZeroTarget_;
  std::optional<Effect> awarenessZeroEffect_;
};

}  // namespace st
