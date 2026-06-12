#pragma once

#include <functional>
#include <string>

namespace st {

class Player;

/// условие доступности выбора/перехода
class Requirement {
 public:
  using Predicate = std::function<bool(const Player&)>;

  Requirement(Predicate predicate, std::string description);

  [[nodiscard]] bool check(const Player& player) const;
  [[nodiscard]] const std::string& description() const noexcept {
    return description_;
  }

  [[nodiscard]] static Requirement minWill(int value);
  [[nodiscard]] static Requirement minAwareness(int value);
  [[nodiscard]] static Requirement maxDarkness(int value);
  [[nodiscard]] static Requirement minDarkness(int value);
  [[nodiscard]] static Requirement hasFlag(std::string flag);
  [[nodiscard]] static Requirement lacksFlag(std::string flag);
  [[nodiscard]] static Requirement hasAnchor(std::string anchorId);
  [[nodiscard]] static Requirement lacksAnchor(std::string anchorId);
  [[nodiscard]] static Requirement minAnchors(int count);
  [[nodiscard]] static Requirement hasItem(std::string itemId);
  [[nodiscard]] static Requirement lacksNote(int number);
  [[nodiscard]] static Requirement custom(Predicate predicate,
                                          std::string description);

 private:
  Predicate predicate_;
  std::string description_;
};

}  // namespace st
