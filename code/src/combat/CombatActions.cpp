#include "st/combat/CombatActions.hpp"

#include "st/Constants.hpp"
#include "st/combat/Enemy.hpp"
#include "st/core/Player.hpp"
#include "st/core/Random.hpp"

namespace st {

    using namespace cfg::combatcfg;

    const std::string& HandStrike::name() const noexcept {
        static const std::string kName = "Ударить рукой";
        return kName;
    }

    std::string HandStrike::execute(Player& player, Enemy& enemy, Random&) {
        player.modifyAwareness(HAND_AWARENESS);
        enemy.takeDamage(HAND_DAMAGE);
        return "Ладонь входит в холодную пустоту. Враг не ранен, но ты чувствуешь, как теряешь форму.";
    }

    const std::string& ThreadStrike::name() const noexcept {
        static const std::string kName = "Ударить Нитью";
        return kName;
    }

    std::string ThreadStrike::execute(Player& player, Enemy& enemy, Random&) {
        player.modifyTension(THREAD_TENSION);
        enemy.takeDamage(THREAD_DAMAGE);
        return "Нить вспыхивает серебром и хлещет, как раскалённая проволока. "
            "Где-то внизу твоё тело выгибается на кровати.";
    }

    Scream::Scream(std::string label) : label_(std::move(label)) {}

    const std::string& Scream::name() const noexcept { return label_; }

    std::string Scream::execute(Player& player, Enemy& enemy, Random&) {
        player.modifyWill(SCREAM_WILL);
        enemy.takeDamage(SCREAM_DAMAGE);
        return "Крик выходит не из горла, а из самого воспоминания. Мир вокруг дрожит.";
    }

    const std::string& MemoryFlash::name() const noexcept {
        static const std::string kName = "Вспышка памяти";
        return kName;
    }

    bool MemoryFlash::isAvailable(const Player& player) const {
        return player.awareness() >= MEMORY_FLASH_REQ;
    }

    std::string MemoryFlash::execute(Player& player, Enemy& enemy, Random&) {
        player.modifyAwareness(MEMORY_FLASH_COST);
        enemy.takeDamage(MEMORY_FLASH_DAMAGE);
        return "Яркое воспоминание о доме ослепляет тьму. Враг отброшен светом.";
    }

    const std::string& Denial::name() const noexcept {
        static const std::string kName = "Разрыв проекции (отрицание)";
        return kName;
    }

    std::string Denial::execute(Player& player, Enemy& enemy, Random& random) {
        if (random.percent(DENIAL_CHANCE)) {
            enemy.takeDamage(enemy.hp());
            return "«Тебя не существует». Враг моргает — и исчезает.";
        }
        player.modifyWill(DENIAL_FAIL_WILL);
        return "Ты повторяешь, что его нет. Но он повторяет вместе с тобой — и его голос увереннее.";
    }

} // namespace st