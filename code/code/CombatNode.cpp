#include "CombatNode.h"

#include <iostream>

#include "Player.h"

CombatNode::CombatNode(std::string nodeId, std::string introText,
                       std::shared_ptr<Enemy> enemyTarget,
                       std::string winSceneId)
    : Node(nodeId, introText), enemy(enemyTarget), victorySceneId(winSceneId) {
  // Генерируем стандартные боевые команды для ментального боя
  // В будущем их можно расширить в зависимости от Осознанности
  addChoice(Choice("Сконцентрировать волю (Атака)", nodeId));
  addChoice(Choice("Разрыв проекции (Защита: -Осознанность, +Воля)", nodeId));
}

void CombatNode::display(const Player& player) const {
  std::cout << "\n=== МЕНТАЛЬНЫЙ БОЙ ===";
  std::cout << "\n" << text;
  std::cout << "\nВраг: " << enemy->getName()
            << " [Стойкость: " << enemy->getHealth() << "]";
  std::cout << "\n=====================\n";
}

std::string CombatNode::processChoice(int choiceIndex, Player& player) {
  if (choiceIndex == 0) {
    // Игрок атакует. Сила атаки зависит, например, от Осознанности
    int damage = 15 + (player.getAwareness() / 5);
    std::cout << "\n[Вы посылаете ментальный импульс! Нанесено " << damage
              << " урона.]\n";
    enemy->takeDamage(damage);
  } else if (choiceIndex == 1) {
    // Защита из GDD механик
    std::cout << "\n[Вы временно ослабляете восприятие, защищая разум. Воля "
                 "частично восстановлена.]\n";
    player.modifyResource(ResourceType::WILL, 15);
    player.modifyResource(ResourceType::AWARENESS, -5);
  }

  // Проверяем, побежден ли враг
  if (enemy->isDead()) {
    std::cout << "\n[" << enemy->getName()
              << " рассеивается в темноте астрала. Путь свободен!]\n";
    return victorySceneId;  // Переход на следующую сюжетную локацию
  }

  // Ответный ход врага, если он жив
  enemy->attack(player);

  return id;  // Возвращаем ID этой же боевой ноды, чтобы цикл боя продолжился
}
