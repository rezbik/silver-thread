#pragma once
#include "Node.h"

#include "Player.h"

std::string Node::processChoice(int choiceIndex, Player& player) {
  if (choiceIndex < 0 || choiceIndex >= static_cast<int>(choices.size())) {
    return id;
  }

  const auto& selectedChoice = choices[choiceIndex];
  selectedChoice.applyEffects(player);
  return selectedChoice.getNextSceneId();
}
