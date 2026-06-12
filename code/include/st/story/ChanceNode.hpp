#pragma once

#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

    class ChanceNode final : public Node {
    public:
        ChanceNode(std::string id, ActStage act, std::string text, int successChancePercent,
            std::string successText, Effect successEffect, std::string successTargetId,
            std::string failText, Effect failEffect, std::string failTargetId)
            : Node(std::move(id), act, std::move(text)),
            successChance_(successChancePercent),
            successText_(std::move(successText)),
            successEffect_(std::move(successEffect)),
            successTarget_(std::move(successTargetId)),
            failText_(std::move(failText)),
            failEffect_(std::move(failEffect)),
            failTarget_(std::move(failTargetId)) {
        }

        void accept(NodeVisitor& visitor) override { visitor.visit(*this); }

        [[nodiscard]] int successChance() const noexcept { return successChance_; }
        [[nodiscard]] const std::string& successText() const noexcept { return successText_; }
        [[nodiscard]] const Effect& successEffect() const noexcept { return successEffect_; }
        [[nodiscard]] const std::string& successTarget() const noexcept { return successTarget_; }
        [[nodiscard]] const std::string& failText() const noexcept { return failText_; }
        [[nodiscard]] const Effect& failEffect() const noexcept { return failEffect_; }
        [[nodiscard]] const std::string& failTarget() const noexcept { return failTarget_; }

    private:
        int successChance_;
        std::string successText_;
        Effect successEffect_;
        std::string successTarget_;
        std::string failText_;
        Effect failEffect_;
        std::string failTarget_;
    };

    }  // namespace st