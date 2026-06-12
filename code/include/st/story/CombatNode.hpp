#pragma once

#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

/// узел боя. хранит спецификацию врага и исходов. бой ведёт Combat.
class CombatNode final : public Node {
 public:
  CombatNode(std::string id, ActStage act, std::string text,
             std::string enemyId, std::string victoryTargetId,
             Effect victoryEffect, std::string awarenessZeroTargetId,
             Effect awarenessZeroEffect)
      : Node(std::move(id), act, std::move(text)),
        enemyId_(std::move(enemyId)),
        victoryTarget_(std::move(victoryTargetId)),
        victoryEffect_(std::move(victoryEffect)),
        awarenessZeroTarget_(std::move(awarenessZeroTargetId)),
        awarenessZeroEffect_(std::move(awarenessZeroEffect)) {}

  void accept(NodeVisitor& visitor) override { visitor.visit(*this); }

  [[nodiscard]] const std::string& enemyId() const noexcept { return enemyId_; }
  [[nodiscard]] const std::string& victoryTarget() const noexcept {
    return victoryTarget_;
  }
  [[nodiscard]] const Effect& victoryEffect() const noexcept {
    return victoryEffect_;
  }
  [[nodiscard]] const std::string& awarenessZeroTarget() const noexcept {
    return awarenessZeroTarget_;
  }
  [[nodiscard]] const Effect& awarenessZeroEffect() const noexcept {
    return awarenessZeroEffect_;
  }

 private:
  std::string enemyId_;
  std::string victoryTarget_;
  Effect victoryEffect_;
  std::string awarenessZeroTarget_;
  Effect awarenessZeroEffect_;
};

}  // namespace st
