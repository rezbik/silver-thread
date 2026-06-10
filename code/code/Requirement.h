#pragma once
#include <string>

#include "Types.h"

class Player;

//  Класс проверки условий для выбора 
class Requirement {
 private:
  RequirementType type;
  int value;
  std::string targetName;  // Имя флага или предмета для проверки

 public:
  Requirement(RequirementType t, int v, std::string target = "")
      : type(t), value(v), targetName(target) {}

  bool check(const Player& player) const;
};
