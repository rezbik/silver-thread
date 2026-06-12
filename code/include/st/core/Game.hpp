#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "st/characters/Characters.hpp"
#include "st/core/GameState.hpp"
#include "st/core/Player.hpp"
#include "st/core/Random.hpp"
#include "st/story/NodeVisitor.hpp"
#include "st/story/StoryTree.hpp"
#include "st/ui/ConsoleView.hpp"

namespace st {

/// контроллер игры. реализует NodeVisitor Ч обрабатывает каждый тип узла.
class Game final : public NodeVisitor {
 public:
  Game(std::unique_ptr<StoryTree> tree, std::unique_ptr<ConsoleView> view,
       std::unique_ptr<Random> random);

  void run();

  void visit(SceneNode& node) override;
  void visit(HubNode& node) override;
  void visit(ChanceNode& node) override;
  void visit(CombatNode& node) override;
  void visit(EndingNode& node) override;
  void visit(FinalBattleNode& node) override;

 private:
  [[nodiscard]] bool processEntry(Node& node);
  void presentNode(Node& node);
  [[nodiscard]] std::optional<std::size_t> selectChoice(
      const std::vector<const Choice*>& choices);
  void applyChoice(const Choice& choice);
  void applyEffect(const Effect& effect, bool softenWhisper);
  void grantItems(const Effect& effect);
  [[nodiscard]] bool checkCritical();
  [[nodiscard]] bool handleInventory();
  void handleActTransition(ActStage nextAct);

  std::unique_ptr<StoryTree> tree_;
  std::unique_ptr<ConsoleView> view_;
  std::unique_ptr<Random> random_;
  Player player_;
  Mimicry mimicry_;
  std::optional<GameState> checkpoint_;
  std::string currentNodeId_;
  std::string pendingNodeId_;
  ActStage currentAct_{ActStage::Prologue};
  bool running_{true};
  bool actBannerShown_{false};
};

}  // namespace st
