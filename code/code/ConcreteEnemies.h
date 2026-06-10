#pragma once

#include <vector>

#include "Enemy.h"

// 1. Теневое Эхо базовый враг, бьет по Воле
class ShadowEcho : public Enemy {
 public:
  ShadowEcho();
  void attack(Player& player) override;
};

// 2. Охотник на паразитов натягивает Нить
class ParasiteHunter : public Enemy {
 public:
  ParasiteHunter();
  void attack(Player& player) override;
};
#pragma once

// 3. Забытая фигура бьет по Осознанности
class ForgottenFigure : public Enemy {
 public:
  ForgottenFigure();
  void attack(Player& player) override;
};

// 4. Двойник копирует статы игрока, наносит урон Чернотой
class Doppelganger : public Enemy {
 public:
  Doppelganger();
  void attack(Player& player) override;
};

// 5. Финальный босс Мимикри
class Mimicry : public Enemy {
 private:
  std::vector<std::string> statements;  // Утверждения (ложь против правды)
  int currentRound = 0;

 public:
  Mimicry();
  void attack(Player& player) override;

  std::string getCurrentStatement() const;
  bool evaluateAnswer(
      int playerChoice,
      Player& player);  // Проверка ответа из диаграммы последовательности
  int getCurrentRound() const { return currentRound; }
};
