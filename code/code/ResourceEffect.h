#pragma once

#include "Types.h"

class Player;

class ResourceEffect {
 private:
  ResourceType resourceType;
  int value;

 public:
  ResourceEffect(ResourceType rType, int val)
      : resourceType(rType), value(val) {}

  void apply(Player& player) const;
};
