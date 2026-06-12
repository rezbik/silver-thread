#pragma once

#include "st/combat/CombatAction.hpp"

namespace st {

    /// Удар рукой: О −5, урона нет.
    class HandStrike final : public CombatAction {
    public:
        [[nodiscard]] const std::string& name() const noexcept override;
        std::string execute(Player& player, Enemy& enemy, Random& random) override;
    };

    /// Удар Нитью: НН +10, урон 5.
    class ThreadStrike final : public CombatAction {
    public:
        [[nodiscard]] const std::string& name() const noexcept override;
        std::string execute(Player& player, Enemy& enemy, Random& random) override;
    };

    /// Крик: В −5, урон 3. Название зависит от врага.
    class Scream final : public CombatAction {
    public:
        explicit Scream(std::string label);
        [[nodiscard]] const std::string& name() const noexcept override;
        std::string execute(Player& player, Enemy& enemy, Random& random) override;

    private:
        std::string label_;
    };

    /// Вспышка памяти: требует О >= 15, стоит О 15, урон 10.
    class MemoryFlash final : public CombatAction {
    public:
        [[nodiscard]] const std::string& name() const noexcept override;
        [[nodiscard]] bool isAvailable(const Player& player) const override;
        std::string execute(Player& player, Enemy& enemy, Random& random) override;
    };

    /// Разрыв проекции (Отрицание): 50/50 — враг исчезает или В −20.
    class Denial final : public CombatAction {
    public:
        [[nodiscard]] const std::string& name() const noexcept override;
        std::string execute(Player& player, Enemy& enemy, Random& random) override;
    };

} // namespace st