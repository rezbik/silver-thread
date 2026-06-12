#pragma once

#include "st/endings/EndingType.hpp"
#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

/// терминальный узел — одна из шести концовок.
class EndingNode final : public Node {
 public:
  EndingNode(std::string id, std::string title, std::string text,
             std::string epilogue, EndingType type)
      : Node(std::move(id), ActStage::Ending, std::move(text)),
        title_(std::move(title)),
        epilogue_(std::move(epilogue)),
        type_(type) {}

  void accept(NodeVisitor& visitor) override { visitor.visit(*this); }

  [[nodiscard]] const std::string& title() const noexcept { return title_; }
  [[nodiscard]] const std::string& epilogue() const noexcept {
    return epilogue_;
  }
  [[nodiscard]] EndingType type() const noexcept { return type_; }

 private:
  std::string title_;
  std::string epilogue_;
  EndingType type_;
};

}  // namespace st
