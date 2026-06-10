#pragma once

#include <map>
#include <memory>
#include <string>

#include "Node.h"
#include "Player.h"

class Game {
 private:
  Player player;
  std::shared_ptr<Node> currentScene;
  std::map<std::string, std::shared_ptr<Node>>
      sceneGraph;  // Граф всех сцен игры
  bool isRunning = true;

  void buildPrologueAndAct1();   // Заполнение стартового контента
  void checkEndingConditions();  // Задел под концовки из UML

 public:
  Game();
  void start();
  void transitionToScene(const std::string& sceneId);
};
