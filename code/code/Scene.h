#pragma once

#include "Node.h"

class SceneNode : public Node {
 public:
  SceneNode(std::string nodeId, std::string nodeText)
      : Node(nodeId, nodeText) {}

  void display(const Player& player) const override;
};
