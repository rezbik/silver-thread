#include "st/story/StoryTree.hpp"

#include <stdexcept>

namespace st {

StoryTree::StoryTree(std::string startNodeId)
    : startNodeId_(std::move(startNodeId)) {}

void StoryTree::addNode(std::shared_ptr<Node> node) {
  if (node == nullptr) {
    throw std::invalid_argument("StoryTree: пустой узел");
  }
  const auto id = node->id();
  if (!nodes_.emplace(id, std::move(node)).second) {
    throw std::logic_error("StoryTree: дублирующийся узел: " + id);
  }
}

const std::shared_ptr<Node>& StoryTree::getNode(const std::string& id) const {
  const auto it = nodes_.find(id);
  if (it == nodes_.end()) {
    throw std::out_of_range("StoryTree: узел не найден: " + id);
  }
  return it->second;
}

}  // namespace st
