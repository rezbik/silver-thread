#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "st/Constants.hpp"
#include "st/mechanics/Types.hpp"
#include "st/story/Requirement.hpp"

namespace st {

class Player;

/// паттерн команда (атомарное изменение состояния игрока)
/// поддерживает условные под-эффекты (when) и нарративные сообщения
class Effect {
 public:
  Effect() = default;

  Effect& will(int delta);
  Effect& awareness(int delta);
  Effect& tension(int delta);
  Effect& darkness(int delta);
  Effect& maxWill(int delta);
  Effect& floorAwareness(int minValue);

  Effect& addFlag(std::string_view flag);
  Effect& addAnchor(std::string_view anchorId);
  Effect& addNote(int number);
  Effect& removeNote(int number);
  Effect& addStatus(StatusEffect status,
                    int charges = cfg::statuscfg::PERMANENT);
  Effect& removeStatus(StatusEffect status);
  Effect& giveItem(std::string_view itemId);
  Effect& message(std::string text);
  Effect& when(Requirement condition, Effect effect);

  /// softenWhisper — защита чашки матери (ослабляет потерю О).
  void apply(Player& player, bool softenWhisper = false,
             std::vector<std::string>* messagesOut = nullptr) const;

  [[nodiscard]] const std::vector<std::string>& items() const noexcept {
    return items_;
  }
  [[nodiscard]] const std::vector<int>& notesAdded() const noexcept {
    return notesAdded_;
  }

 private:
  int will_{0};
  int awareness_{0};
  int tension_{0};
  int darkness_{0};
  int maxWill_{0};
  std::optional<int> awarenessFloor_;

  std::vector<std::string> flags_;
  std::vector<std::string> anchors_;
  std::vector<int> notesAdded_;
  std::vector<int> notesRemoved_;
  std::vector<std::pair<StatusEffect, int>> statusesAdded_;
  std::vector<StatusEffect> statusesRemoved_;
  std::vector<std::string> items_;
  std::string message_;
  std::vector<std::pair<Requirement, std::shared_ptr<const Effect>>>
      conditionals_;
};

}  // namespace st
