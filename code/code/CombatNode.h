#pragma once

#include <memory>

#include "Enemy.h"
#include "Node.h"

// ”зел боевого столкновени¤, наследуетс¤ от Node (ѕакет Story/Combat в UML)
class CombatNode : public Node {
 private:
  std::shared_ptr<Enemy> enemy;
  std::string victorySceneId;  //  уда перейти в случае победы

 public:
  CombatNode(std::string nodeId, std::string introText,
             std::shared_ptr<Enemy> enemyTarget, std::string winSceneId);

  // ѕереопредел¤ем отображение и логику выбора дл¤ боевой фазы
  void display(const Player& player) const override;
  std::string processChoice(int choiceIndex, Player& player) override;
};
