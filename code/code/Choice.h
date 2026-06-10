#pragma once

#include <string>
#include <vector>

#include "Requirement.h"
#include "ResourceEffect.h"

class Player;

class Choice {
 private:
  std::string text;
  std::string nextSceneId;  // ID сцены, куда ведет выбор
  std::vector<Requirement> requirements;
  std::vector<ResourceEffect> effects;
  bool isParasitic;  // Механика ложных вариантов от Мимикри [cite: 2, 76]

 public:
  Choice(std::string txt, std::string nextId, bool parasitic = false)
      : text(txt), nextSceneId(nextId), isParasitic(parasitic) {}

  void addRequirement(const Requirement& req) { requirements.push_back(req); }
  void addEffect(const ResourceEffect& eff) { effects.push_back(eff); }

  std::string getText() const { return text; }
  std::string getNextSceneId() const { return nextSceneId; }
  bool getIsParasitic() const { return isParasitic; }

  bool isAvailable(const Player& player) const;
  void applyEffects(Player& player) const;
};
