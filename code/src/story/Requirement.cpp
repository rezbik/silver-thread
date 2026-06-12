#include "st/story/Requirement.hpp"

#include "st/core/Player.hpp"

namespace st {

    Requirement::Requirement(Predicate predicate, std::string description)
        : predicate_(std::move(predicate)), description_(std::move(description)) {
    }

    bool Requirement::check(const Player& player) const { return predicate_(player); }

    Requirement Requirement::minWill(int value) {
        return { [value](const Player& p) { return p.will() >= value; }, "Воля >= " + std::to_string(value) };
    }

    Requirement Requirement::minAwareness(int value) {
        return { [value](const Player& p) { return p.awareness() >= value; },
                "Осознанность >= " + std::to_string(value) };
    }

    Requirement Requirement::maxDarkness(int value) {
        return { [value](const Player& p) { return p.darkness() <= value; },
                "Чернота <= " + std::to_string(value) };
    }

    Requirement Requirement::minDarkness(int value) {
        return { [value](const Player& p) { return p.darkness() >= value; },
                "Чернота >= " + std::to_string(value) };
    }

    Requirement Requirement::hasFlag(std::string flag) {
        return { [flag](const Player& p) { return p.hasFlag(flag); }, "флаг: " + flag };
    }

    Requirement Requirement::lacksFlag(std::string flag) {
        return { [flag](const Player& p) { return !p.hasFlag(flag); }, "нет флага: " + flag };
    }

    Requirement Requirement::hasAnchor(std::string anchorId) {
        return { [anchorId](const Player& p) { return p.hasAnchor(anchorId); }, "якорь: " + anchorId };
    }

    Requirement Requirement::lacksAnchor(std::string anchorId) {
        return { [anchorId](const Player& p) { return !p.hasAnchor(anchorId); },
                "нет якоря: " + anchorId };
    }

    Requirement Requirement::minAnchors(int count) {
        return { [count](const Player& p) { return p.anchorCount() >= count; },
                "якорей >= " + std::to_string(count) };
    }

    Requirement Requirement::hasItem(std::string itemId) {
        return { [itemId](const Player& p) { return p.inventory().contains(itemId); },
                "предмет: " + itemId };
    }

    Requirement Requirement::lacksNote(int number) {
        return { [number](const Player& p) { return !p.hasNote(number); },
                "нет записки №" + std::to_string(number) };
    }

    Requirement Requirement::custom(Predicate predicate, std::string description) {
        return { std::move(predicate), std::move(description) };
    }

} // namespace st