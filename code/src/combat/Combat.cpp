#include "st/combat/Combat.hpp"

#include "st/Constants.hpp"
#include "st/combat/CombatActions.hpp"
#include "st/core/Player.hpp"
#include "st/core/Random.hpp"
#include "st/ui/ConsoleView.hpp"

namespace st {

Combat::Combat(Player& player, std::unique_ptr<Enemy> enemy, ConsoleView& view,
               Random& random)
    : player_(player), enemy_(std::move(enemy)), view_(view), random_(random) {
  actions_.push_back(std::make_unique<HandStrike>());
  actions_.push_back(std::make_unique<ThreadStrike>());
  actions_.push_back(std::make_unique<Scream>(enemy_->screamLabel()));
  actions_.push_back(std::make_unique<MemoryFlash>());
  actions_.push_back(std::make_unique<Denial>());
}

CombatResult Combat::run() {
  view_.showCombatIntro(*enemy_);

  while (true) {
    view_.showCombatState(player_, *enemy_);

    std::vector<const CombatAction*> available;
    for (const auto& action : actions_) {
      if (action->isAvailable(player_)) {
        available.push_back(action.get());
      }
    }

    const std::size_t chosen = view_.chooseCombatAction(available);
    for (const auto& action : actions_) {
      if (action.get() == available[chosen]) {
        view_.showSystemMessage(action->execute(player_, *enemy_, random_));
        break;
      }
    }

    if (player_.isThreadBroken()) {
      return CombatResult::ThreadBreak;
    }
    if (enemy_->isDefeated()) {
      view_.showSystemMessage(enemy_->defeatText());
      return CombatResult::Victory;
    }

    view_.showSystemMessage(enemy_->attackText());
    player_.modifyAwareness(cfg::combatcfg::ENEMY_AWARENESS_HIT);

    if (player_.awareness() <= 0) {
      return CombatResult::AwarenessCollapse;
    }
    if (player_.isThreadBroken()) {
      return CombatResult::ThreadBreak;
    }
  }
}

}  // namespace st
