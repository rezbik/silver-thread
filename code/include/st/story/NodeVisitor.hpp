#pragma once

namespace st {

class SceneNode;
class HubNode;
class ChanceNode;
class CombatNode;
class EndingNode;
class FinalBattleNode;

/// Game обрабатывает каждый тип узла по-своему
class NodeVisitor {
 public:
  virtual ~NodeVisitor() = default;
  virtual void visit(SceneNode& node) = 0;
  virtual void visit(HubNode& node) = 0;
  virtual void visit(ChanceNode& node) = 0;
  virtual void visit(CombatNode& node) = 0;
  virtual void visit(EndingNode& node) = 0;
  virtual void visit(FinalBattleNode& node) = 0;
};

}  // namespace st
