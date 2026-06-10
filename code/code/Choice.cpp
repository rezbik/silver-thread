#include "Choice.h"

#include "Player.h"
#include "ResourceEffect.h"

void ResourceEffect::apply(Player& player) const {
  player.modifyResource(resourceType, value);
}
bool Choice::isAvailable(const Player& player) const {
  for (const auto& req : requirements) {
    if (!req.check(player)) return false;
  }
  return true;
}

void Choice::applyEffects(Player& player) const {
  for (const auto& eff : effects) {
    eff.apply(player);
  }
}
