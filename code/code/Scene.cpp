#include "Scene.h"

#include <iostream>

#include "Player.h"

void SceneNode::display(const Player& player) const {
  if (player.hasStatus("Grounded_Blind")) {
    std::cout << "\n[Твои чувства притуплены, ты слышишь только далекий "
                 "скрежет...]\n";
    return;
  }
  std::cout << "\n" << text << "\n";
}
