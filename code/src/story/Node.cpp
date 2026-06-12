#include "st/story/Node.hpp"

namespace st {

    Node::Node(std::string id, ActStage act, std::string text)
        : id_(std::move(id)), act_(act), text_(std::move(text)) {
    }

    Node& Node::setEntryEffect(Effect effect) {
        entryEffect_ = std::move(effect);
        return *this;
    }

    Node& Node::addRedirect(Requirement condition, std::string targetId) {
        redirects_.emplace_back(std::move(condition), std::move(targetId));
        return *this;
    }

    std::optional<std::string> Node::checkRedirect(const Player& player) const {
        for (const auto& [condition, targetId] : redirects_) {
            if (condition.check(player)) {
                return targetId;
            }
        }
        return std::nullopt;
    }

    Node& Node::addChoice(Choice choice) {
        choices_.push_back(std::move(choice));
        return *this;
    }

    std::vector<const Choice*> Node::availableChoices(const Player& player) const {
        std::vector<const Choice*> result;
        for (const auto& choice : choices_) {
            if (choice.isAvailable(player)) {
                result.push_back(&choice);
            }
        }
        return result;
    }

} // namespace st