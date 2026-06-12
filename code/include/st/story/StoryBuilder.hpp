#pragma once

#include <memory>

#include "st/story/StoryTree.hpp"

namespace st {

/// собирает полное сюжетное дерево
class StoryBuilder {
 public:
  [[nodiscard]] std::unique_ptr<StoryTree> build() const;

 private:
  void buildPrologue(StoryTree& tree) const;
  void buildAct1(StoryTree& tree) const;
  void buildAct2(StoryTree& tree) const;
  void buildAct3(StoryTree& tree) const;
  void buildEndings(StoryTree& tree) const;
};

}  // namespace st
