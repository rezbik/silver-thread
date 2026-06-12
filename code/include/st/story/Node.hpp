#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "st/mechanics/Types.hpp"
#include "st/story/Choice.hpp"
#include "st/story/Effect.hpp"
#include "st/story/Requirement.hpp"

namespace st {

class NodeVisitor;
class Player;

/// базовый узел сюжетного дерева (Composite). узел может иметь:
/// эффект входа, условные редиректы и список выборов
class Node {
 public:
  Node(std::string id, ActStage act, std::string text);
  virtual ~Node() = default;

  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  virtual void accept(NodeVisitor& visitor) = 0;

  [[nodiscard]] const std::string& id() const noexcept { return id_; }
  [[nodiscard]] ActStage act() const noexcept { return act_; }
  [[nodiscard]] const std::string& text() const noexcept { return text_; }

  Node& setEntryEffect(Effect effect);
  [[nodiscard]] const std::optional<Effect>& entryEffect() const noexcept {
    return entryEffect_;
  }

  Node& addRedirect(Requirement condition, std::string targetId);
  [[nodiscard]] std::optional<std::string> checkRedirect(
      const Player& player) const;

  Node& addChoice(Choice choice);
  [[nodiscard]] std::vector<const Choice*> availableChoices(
      const Player& player) const;

 private:
  std::string id_;
  ActStage act_;
  std::string text_;
  std::optional<Effect> entryEffect_;
  std::vector<std::pair<Requirement, std::string>> redirects_;
  std::vector<Choice> choices_;
};

}  // namespace st
