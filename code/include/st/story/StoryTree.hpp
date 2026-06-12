#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "st/story/Node.hpp"

namespace st {

/// хранилище сюжетного графа
class StoryTree {
 public:
  explicit StoryTree(std::string startNodeId);

  void addNode(std::shared_ptr<Node> node);
  [[nodiscard]] const std::shared_ptr<Node>& getNode(
      const std::string& id) const;
  [[nodiscard]] const std::string& startNodeId() const noexcept {
    return startNodeId_;
  }

 private:
  std::string startNodeId_;
  std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
};

}  // namespace st
