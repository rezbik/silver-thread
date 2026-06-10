#pragma once

#include <string>
#include <vector>

#include "Choice.h"

class Player;

// Базовый класс для всех типов узлов истории (из UML пакета Story)
class Node {
 protected:
  std::string id;
  std::string text;
  std::vector<Choice> choices;

 public:
  Node(std::string nodeId, std::string nodeText) : id(nodeId), text(nodeText) {}
  virtual ~Node() = default;

  std::string getId() const { return id; }
  virtual void display(const Player& player) const = 0;  // Нарративный вывод

  const std::vector<Choice>& getChoices() const { return choices; }
  void addChoice(const Choice& choice) { choices.push_back(choice); }

  // Метод будущего расширения для обработки специфики нод (например, боя или
  // финала)
  virtual std::string processChoice(int choiceIndex, Player& player);
};
