#pragma once

#include "st/items/Item.hpp"

namespace st {

    /// „ашка матери Ч пассивна¤ защита от шЄпота ћимикри (ослабл¤ет потерю ќ вдвое).
    class MotherCup final : public Item {
    public:
        MotherCup();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
    };

    /// ƒневник Ч даЄт +ќ при чтении, одно использование за акт.
    class Diary final : public Item {
    public:
        Diary();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
        void onActChanged() override;

    private:
        bool usedThisAct_{ false };
    };

    /// ќсколок зеркала Ч можно осв¤тить и создать точку ¤корени¤.
    class MirrorShard final : public Item {
    public:
        MirrorShard();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
        [[nodiscard]] bool isConsecrated() const noexcept { return consecrated_; }

    private:
        bool consecrated_{ false };
    };

    /// ∆ест¤на¤ звезда Ёхо Ч тЄплый союзный отклик (бонус в «еркале любви).
    class TinStar final : public Item {
    public:
        TinStar();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
    };

    /// ѕеро јрхивариуса Ч помечает паразитические выборы ћимикри.
    class ArchivistFeather final : public Item {
    public:
        ArchivistFeather();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
    };

    /// «ажигалка Ч свет в астральном тумане (расширенна¤ верси¤).
    class Lighter final : public Item {
    public:
        Lighter();
        [[nodiscard]] std::shared_ptr<Item> clone() const override;
        UseResult use(Player& player) override;
    };

} // namespace st