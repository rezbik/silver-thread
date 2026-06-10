#include "ConcreteEnemies.h"

#include <iostream>

#include "Player.h"

ShadowEcho::ShadowEcho() : Enemy("Теневое Эхо", 40, 10) {}
void ShadowEcho::attack(Player& player) {
  std::cout << "\n[" << name << " шепчет забытые обиды, подрывая твою Волю!]\n";
  player.modifyResource(ResourceType::WILL, -baseDamage);
}

ParasiteHunter::ParasiteHunter() : Enemy("Охотник на паразитов", 70, 15) {}
void ParasiteHunter::attack(Player& player) {
  std::cout << "\n[" << name
            << " вонзает когти в пространство, натягивая Серебряную нить!]\n";
  player.modifyResource(ResourceType::THREAD_TENSION, 15);
  player.modifyResource(ResourceType::WILL, -5);
}
// Реализация Забытой Фигуры
ForgottenFigure::ForgottenFigure() : Enemy("Забытая фигура", 50, 8) {}
void ForgottenFigure::attack(Player& player) {
  std::cout << "\n[" << name
            << " заставляет тебя сомневаться в собственных воспоминаниях!]\n";
  player.modifyResource(ResourceType::AWARENESS, -baseDamage);
}

// Реализация Двойника
Doppelganger::Doppelganger() : Enemy("Двойник", 80, 12) {}
void Doppelganger::attack(Player& player) {
  std::cout << "\n[" << name
            << " смотрит на тебя твоими же глазами. Нить темнеет...]\n";
  player.modifyResource(ResourceType::THREAD_DARKNESS, 10);
  player.modifyResource(ResourceType::WILL, -baseDamage);
}

// Реализация Финального Босса Мимикри
Mimicry::Mimicry() : Enemy("Мимикри", 150, 0) {
  statements.push_back("Я идеальная версия тебя. У меня нет твоих страхов.");
  statements.push_back(
      "Твои близкие даже не заметят подмены. Им со мной будет лучше.");
  statements.push_back(
      "Ты всего лишь блеклое эхо, застрявшее в коме. Отдай мне тело.");
}

std::string Mimicry::getCurrentStatement() const {
  if (currentRound < static_cast<int>(statements.size())) {
    return statements[currentRound];
  }
  return "Ты все еще цепляешься за эту грязную реальность?";
}

bool Mimicry::evaluateAnswer(int playerChoice, Player& player) {
  // Согласно диаграмме последовательности:
  // Отрицание лжи - правильный путь, снижает Тьму или бьет босса.
  // Согласие со слабостью - увеличивает Тьму, штрафует Осознанность.

  bool isCorrect = (playerChoice == 1);

  if (isCorrect) {
    std::cout << "\n[Твоя правда ранит Мимикри! Его уверенность колеблется.]\n";
    takeDamage(50);
    player.modifyResource(ResourceType::THREAD_DARKNESS, -5);
  } else {
    int penalty = 15;
    if (player.hasStatus("Exhaustion")) {
      penalty *= 2;
      std::cout
          << "\n[Из-за Истощения (Exhaustion) ментальный удар удваивается!]\n";
    }
    std::cout << "\n[Ложь проникает под кожу. Осознанность падает.]\n";
    player.modifyResource(ResourceType::AWARENESS, -penalty);
    player.modifyResource(ResourceType::THREAD_DARKNESS, 15);
  }

  currentRound++;
  return isCorrect;
}

void Mimicry::attack(Player& player) {
  // Вся атака Мимикри идет через раунды допроса evaluateAnswer
}
