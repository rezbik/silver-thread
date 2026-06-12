#pragma once

#include "st/story/Node.hpp"
#include "st/story/NodeVisitor.hpp"

namespace st {

/// хаб-локация акта (квартира, Лимб)
class HubNode final : public Node {
 public:
  using Node::Node;
  void accept(NodeVisitor& visitor) override { visitor.visit(*this); }
};

}  // namespace st
