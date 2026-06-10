#include "Game.h"

#include <windows.h>

#include <iostream>

#include "CombatNode.h"
#include "ConcreteEnemies.h"
#include "QuestItems.h"
#include "Scene.h"

Game::Game() { buildPrologueAndAct1(); }

void clearScreen() {
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord = {0, 0};
  DWORD count;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
    // Заполняем всю консоль пробелами
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ',
                               csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    // Сбрасываем атрибуты текста
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes,
                               csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    // Возвращаем курсор в верхний левый угол (0,0)
    SetConsoleCursorPosition(hStdOut, coord);
  }
}

void Game::buildPrologueAndAct1() {
  // 1. Стартовая сцена
  auto prologue = std::make_shared<SceneNode>(
      "prologue_start",
      "Ты засыпаешь. Текст теряет четкость. Ты просыпаешься НАД своим телом.\n"
      "Нить — тонкая светящаяся линия, тянется от твоей груди в темноту угла.");

  Choice c1("Коснуться своего тела (Ошибка)", "astral_drop");
  c1.addEffect(ResourceEffect(ResourceType::WILL, -15));
  c1.addEffect(ResourceEffect(ResourceType::THREAD_TENSION, 20));

  Choice c2("Изучить Нить", "study_thread");
  c2.addEffect(ResourceEffect(ResourceType::AWARENESS, 10));

  prologue->addChoice(c1);
  prologue->addChoice(c2);
  sceneGraph[prologue->getId()] = prologue;

  // 2. Ветка изучения нити (Дает предмет Дневник)
  auto studyThread = std::make_shared<SceneNode>(
      "study_thread",
      "Вы концентрируетесь на Нити. Под кроватью вы замечаете старую тетрадь.");
  Choice c3("Взять Потертый Дневник", "act1_hub");
  studyThread->addChoice(c3);
  sceneGraph[studyThread->getId()] = studyThread;

  // 3. Падение в Астрал (Боевая нода с Теневым Эхом)
  auto enemyEcho = std::make_shared<ShadowEcho>();
  auto combatDrop =
      std::make_shared<CombatNode>("astral_drop",
                                   "Пространство разорвалось! Из углов комнаты "
                                   "к твоей нити тянутся блеклые руки.",
                                   enemyEcho, "act1_hub");
  sceneGraph[combatDrop->getId()] = combatDrop;

  // 4. Хаб Первого Акта (Квартира)
  auto act1Hub = std::make_shared<SceneNode>(
      "act1_hub",
      "--- АКТ 1: ЭХО ДОМА ---\n"
      "Ты находишься в призрачной копии своей квартиры. Дверь наружу заперта "
      "ментальным замком.");

  Choice cHub1("Использовать Дневник (Требуется: Дневник в инвентаре)",
               "open_door");
  // Требование наличия предмета
  cHub1.addRequirement(
      Requirement(RequirementType::HAS_ITEM, 0, "Потертый Дневник"));

  Choice cHub2("Искать другой выход (Вступить в бой с Охотником)",
               "hunter_fight");

  act1Hub->addChoice(cHub1);
  act1Hub->addChoice(cHub2);
  sceneGraph[act1Hub->getId()] = act1Hub;

  // Сцены продолжения
  sceneGraph["open_door"] =
      std::make_shared<SceneNode>("open_door",
                                  "Замок поддался силе твоих воспоминаний! "
                                  "Путь в Город Теней (Акт 2) открыт.");

  auto hunter = std::make_shared<ParasiteHunter>();
  sceneGraph["hunter_fight"] = std::make_shared<CombatNode>(
      "hunter_fight",
      "Из зеркала в прихожей вырывается долгое костлявое существо!", hunter,
      "open_door");

  // Начальное состояние
  currentScene = sceneGraph["prologue_start"];

  // Сразу выдадим игроку Чашку Матери для тестов инвентаря
  player.getInventory().addItem(std::make_shared<MotherCup>());
}

void Game::transitionToScene(const std::string& sceneId) {
  if (sceneGraph.find(sceneId) != sceneGraph.end()) {
    currentScene = sceneGraph[sceneId];
  } else {
    std::cout << "\n[Переход к сцене " << sceneId
              << ". Описание заложено в архитектуру концовок!]\n";
  }
}

void Game::checkEndingConditions() {
  // Концовка Д из диаграммы состояний: Смерть по Воле или критическое Натяжение
  // нити
  if (player.getWill() <= 0 || player.getThreadTension() >= 100) {
    std::cout << "\n=============================================";
    std::cout << "\nКОНЦОВКА Д: РАЗРЫВ СЕРЕБРЯНОЙ НИТИ.";
    std::cout
        << "\nТвоя ментальная связь лопнула. Мимикри навсегда занял тело.";
    std::cout << "\n=============================================\n";
    isRunning = false;
  }
}

void Game::start() {
  std::cout << "--- СЕРЕБРЯНАЯ НИТЬ (Архитектурный каркас собран) ---\n";

  while (isRunning) {
    clearScreen();
    currentScene->display(player);
    // Отображение статус-бара игрока
    std::cout << "\n=======================================================";
    std::cout << "\n[Воля: " << player.getWill()
              << "% | Осознанность: " << player.getAwareness()
              << " | Натяжение Нити: " << player.getThreadTension()
              << "% | Тьма: " << player.getThreadDarkness() << "]";
    std::cout << "\n=======================================================\n";

    const auto& choices = currentScene->getChoices();

    // Вывод вариантов действий
    for (size_t i = 0; i < choices.size(); ++i) {
      std::cout << i + 1 << ". " << choices[i].getText();
      if (!choices[i].isAvailable(player)) {
        std::cout << " (Заблокировано)";
      }
      std::cout << "\n";
    }

    // Всегда доступные системные команды
    std::cout << "9. Открыть Инвентарь\n";
    std::cout << "0. Выйти из игры\n";

    std::cout << "\nВыберите действие: ";
    int input;
    std::cin >> input;

    if (input == 0) {
      isRunning = false;
      break;
    }

    // Логика Инвентаря
    if (input == 9) {
      auto& invItems = player.getInventory().getItems();
      if (invItems.empty()) {
        std::cout << "\n[Инвентарь пуст]\n";
      } else {
        std::cout << "\n--- ИНВЕНТАРЬ (Макс. 4 слота) ---";
        for (size_t i = 0; i < invItems.size(); ++i) {
          std::cout << "\n"
                    << i + 1 << ". " << invItems[i]->getName() << " -> "
                    << invItems[i]->getDescription();
        }
        std::cout << "\n0. Назад";
        std::cout << "\nВыберите предмет для использования: ";
        int invInput;
        std::cin >> invInput;
        if (invInput > 0 && invInput <= static_cast<int>(invItems.size())) {
          auto chosenItem = invItems[invInput - 1];
          chosenItem->use(player);
          if (chosenItem->getIsConsumable()) {
            player.getInventory().removeItem(chosenItem);
          }
        }
      }
      continue;
    }

    int idx = input - 1;
    if (idx >= 0 && idx < static_cast<int>(choices.size()) &&
        choices[idx].isAvailable(player)) {
      // Если игрок выбрал взять Дневник на сцене изучения, добавляем его в
      // инвентарь
      if (currentScene->getId() == "study_thread" && idx == 0) {
        player.getInventory().addItem(std::make_shared<Diary>());
        std::cout << "\n[Предмет 'Потертый Дневник' добавлен в инвентарь!]\n";
      }

      std::string nextId = currentScene->processChoice(idx, player);
      transitionToScene(nextId);
    } else {
      std::cout
          << "\nНеверный ввод или действие заблокировано требованиями UML!\n";
    }

    checkEndingConditions();
  }
}
