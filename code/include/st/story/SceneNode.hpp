#pragma once

#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

/// обычная сцена
class SceneNode : public Node {
 public:
  using Node::Node;

  void accept(NodeVisitor& visitor) override { visitor.visit(*this); }

  SceneNode& setVisitPenalty(int visitThreshold, Effect penalty,
                             std::string penaltyText) {
    visitThreshold_ = visitThreshold;
    penaltyEffect_ = std::move(penalty);
    penaltyText_ = std::move(penaltyText);
    return *this;
  }

  [[nodiscard]] bool registerVisitAndCheckPenalty() {
    if (visitThreshold_ <= 0 || penaltyApplied_) {
      return false;
    }
    if (++visitCount_ >= visitThreshold_) {
      penaltyApplied_ = true;
      return true;
    }
    return false;
  }

  [[nodiscard]] const Effect& penaltyEffect() const noexcept {
    return penaltyEffect_;
  }
  [[nodiscard]] const std::string& penaltyText() const noexcept {
    return penaltyText_;
  }

 private:
  int visitThreshold_{0};
  int visitCount_{0};
  bool penaltyApplied_{false};
  Effect penaltyEffect_;
  std::string penaltyText_;
};

}  // namespace st
