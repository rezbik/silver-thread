#pragma once

#include <set>
#include <string>
#include <vector>

#include "Inventory.h"
#include "Types.h"

class Player {
 private:
  // Параметры из UML-класса Player
  int will = 100;
  int awareness = 50;
  int threadTension = 0;
  int threadDarkness = 0;
  const int maxWill = 100;

  Inventory inventory;
  std::vector<Anchor> anchors;
  std::vector<DreamerNote> notes;
  std::set<std::string>
      flags;  // Квестовые флаги (например, "Принята правда Двойника") [cite: 3]
  std::vector<std::string> statuses;  // Состояния (например, "Чужая рука",
                                      // "Exhaustion") [cite: 3, 5]

 public:
  Player() = default;

  // Методы изменения состояния из UML
  void modifyResource(ResourceType type, int value);
  bool checkCriticalState();  // Проверка на смерть (Воля <= 0) или разрыв Нити
                              // [cite: 2, 27]

  void addAnchor(const Anchor& anchor);
  void addNote(const DreamerNote& note);
  void addFlag(const std::string& flag);
  bool hasFlag(const std::string& flag) const;
  bool hasStatus(const std::string& status) const;
  void addStatus(const std::string& status);

  // Геттеры для проверок требований
  int getWill() const { return will; }
  int getAwareness() const { return awareness; }
  int getThreadTension() const { return threadTension; }
  int getThreadDarkness() const { return threadDarkness; }
  const Inventory& getInventory() const { return inventory; }
  Inventory& getInventory() { return inventory; }
};
