#pragma once

#include <string>

class Player;

// Базовый класс противника из UML
class Enemy {
 protected:
  std::string name;
  int health;  // В ментальном бою это может быть "Стойкость" или "Энергия
               // искажения"
  int baseDamage;

 public:
  Enemy(std::string name, int health, int damage)
      : name(name), health(health), baseDamage(damage) {}

  virtual ~Enemy() = default;

  std::string getName() const { return name; }
  int getHealth() const { return health; }
  bool isDead() const { return health <= 0; }

  void takeDamage(int amount);

  // Виртуальный метод атаки врага (каждый атакует по-своему согласно GDD)
  virtual void attack(Player& player) = 0;
};
