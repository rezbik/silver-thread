#pragma once

#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

/// узел финальной битвы правды и лжи (логика — в endings::FinalBattle)
class FinalBattleNode final : public Node {
 public:
  using Node::Node;
  void accept(NodeVisitor& visitor) override { visitor.visit(*this); }
};

}  // namespace st
