#include "st/combat/Enemy.hpp"

#include <algorithm>
#include <stdexcept>

#include "st/Constants.hpp"

namespace st {

    void Enemy::takeDamage(int amount) { hp_ = std::max(0, hp_ - amount); }

    ShadowEcho::ShadowEcho()
        : Enemy("Тень-отголосок", cfg::combatcfg::SHADOW_HP,
            "Тень тянет пальцы к твоей Нити. Холод проходит сквозь мысли.",
            "Свет воспоминания пробивает Тень насквозь. Она съёживается, будто бумага в огне.",
            "Закричать") {
    }

    ForgottenNameFigure::ForgottenNameFigure()
        : Enemy("Фигура забытого имени", cfg::combatcfg::FIGURE_HP,
            "Фигура из чёрной плоти тянется к тебе, и твоё имя становится тише.",
            "Фигура рассыпается на чёрные капли. На миг в каждой отражается твоё лицо — "
            "забытое, но ещё не потерянное.",
            "Закричать своё имя") {
    }

    std::unique_ptr<Enemy> EnemyFactory::create(const std::string& enemyId) {
        if (enemyId == enemyid::SHADOW_ECHO) {
            return std::make_unique<ShadowEcho>();
        }
        if (enemyId == enemyid::FORGOTTEN_FIGURE) {
            return std::make_unique<ForgottenNameFigure>();
        }
        throw std::invalid_argument("EnemyFactory: неизвестный враг: " + enemyId);
    }

} // namespace st