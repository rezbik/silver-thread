#include "Requirement.h"

#include "Player.h"

bool Requirement::check(const Player& player) const {
  switch (type) {
    case RequirementType::AWARENESS_MIN:
      return player.getAwareness() >= value;
    case RequirementType::WILL_MIN:
      return player.getWill() >= value;
    case RequirementType::HAS_FLAG:
      return player.hasFlag(targetName);
    case RequirementType::HAS_ITEM:
      return player.getInventory().hasItem(targetName);
    case RequirementType::THREAD_DARKNESS_MAX:
      return player.getThreadDarkness() <= value;
    default:
      return true;
  }
}
