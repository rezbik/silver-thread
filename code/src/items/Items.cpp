#include "st/items/Items.hpp"

#include "st/Constants.hpp"
#include "st/core/Player.hpp"
#include "st/mechanics/Types.hpp"

namespace st {

    MotherCup::MotherCup()
        : Item(std::string(itemsid::MOTHER_CUP), "Чашка матери",
            "Кружка с отбитым краем. Пока она с тобой, шёпот Мимикри слабее.") {
    }

    std::shared_ptr<Item> MotherCup::clone() const { return std::make_shared<MotherCup>(*this); }

    Item::UseResult MotherCup::use(Player&) {
        return { .text = "Ты держишь чашку. Пар поднимается, хотя чай давно холодный. "
                        "Её тепло работает само — просто не забывай её." };
    }

    Diary::Diary()
        : Item(std::string(itemsid::DIARY), "Дневник",
            "Дневник в кожаной обложке. Чтение проясняет мысли (раз за акт).") {
    }

    std::shared_ptr<Item> Diary::clone() const { return std::make_shared<Diary>(*this); }

    Item::UseResult Diary::use(Player& player) {
        if (usedThisAct_) {
            return { .text = "Страницы пусты — дневник уже отдал всё, что мог в этом акте." };
        }
        usedThisAct_ = true;
        player.modifyAwareness(cfg::itemcfg::DIARY_USE_AWARE);
        return { .text = "Знакомый почерк выравнивает мысли. Осознанность растёт." };
    }

    void Diary::onActChanged() { usedThisAct_ = false; }

    MirrorShard::MirrorShard()
        : Item(std::string(itemsid::MIRROR_SHARD), "Осколок зеркала",
            "Острый осколок. Его можно освятить и превратить в точку якорения.") {
    }

    std::shared_ptr<Item> MirrorShard::clone() const { return std::make_shared<MirrorShard>(*this); }

    Item::UseResult MirrorShard::use(Player& player) {
        if (consecrated_) {
            return { .text = "Осколок уже освящён. Нить помнит к нему дорогу." };
        }
        consecrated_ = true;
        player.modifyAwareness(cfg::itemcfg::SHARD_CONSECRATE_AWARE);
        player.modifyWill(cfg::itemcfg::SHARD_CONSECRATE_WILL);
        return { .text = "Ты вливаешь в осколок частицу себя. Он начинает светиться ровным "
                        "серебряным светом. Если Нить порвётся — она притянет тебя сюда.",
                .consecrated = true };
    }

    TinStar::TinStar()
        : Item(std::string(itemsid::TIN_STAR), "Жестяная звезда Эхо",
            "Звезда девочки из Лимба. Иногда теплеет в темноте.") {
    }

    std::shared_ptr<Item> TinStar::clone() const { return std::make_shared<TinStar>(*this); }

    Item::UseResult TinStar::use(Player&) {
        return { .text = "Звезда чуть тёплая. Где-то рядом — Эхо. «Я верну, когда станет темно»." };
    }

    ArchivistFeather::ArchivistFeather()
        : Item(std::string(itemsid::ARCHIVIST_FEATHER), "Перо Архивариуса",
            "Пепельное перо из украденной страницы. Помечает ложные выборы Мимикри.") {
    }

    std::shared_ptr<Item> ArchivistFeather::clone() const {
        return std::make_shared<ArchivistFeather>(*this);
    }

    Item::UseResult ArchivistFeather::use(Player&) {
        return { .text = "Перо подрагивает, готовое отметить чужую волю чёрным росчерком." };
    }

    Lighter::Lighter()
        : Item(std::string(itemsid::LIGHTER), "Зажигалка",
            "Старая зажигалка из реальности. Даёт свет в астральном тумане.") {
    }

    std::shared_ptr<Item> Lighter::clone() const { return std::make_shared<Lighter>(*this); }

    Item::UseResult Lighter::use(Player&) {
        return { .text = "Маленький огонёк. Туман отступает на шаг — этого достаточно." };
    }

} // namespace st