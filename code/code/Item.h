#pragma once

#include <memory>
#include <string>

class Player;

// Абстрактный базовый класс предмета из UML
class Item {
 protected:
  std::string name;
  std::string description;
  bool isConsumable;  // Расходуемый ли предмет

 public:
  Item(std::string name, std::string desc, bool consumable = false)
      : name(name), description(desc), isConsumable(consumable) {}

  virtual ~Item() = default;

  std::string getName() const { return name; }
  std::string getDescription() const { return description; }
  bool getIsConsumable() const { return isConsumable; }

  // Чистая виртуальная функция использования предмета
  virtual void use(Player& player) = 0;
};
