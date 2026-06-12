#include "st/ui/ConsoleView.hpp"

#include <iostream>
#include <limits>

#include "st/Constants.hpp"
#include "st/combat/CombatAction.hpp"
#include "st/combat/Enemy.hpp"
#include "st/core/Inventory.hpp"
#include "st/core/Player.hpp"
#include "st/mechanics/Types.hpp"
#include "st/story/Choice.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace st {

namespace {

constexpr std::string_view kSeparator =
    "----------------------------------------------------------------";

std::string threadStateLabel(ThreadState state) {
  switch (state) {
    case ThreadState::Silver:
      return "Нить серебристо светится.";
    case ThreadState::Tense:
      return "Нить звенит даже без движения. Каждый шаг отдаётся болью "
             "в груди спящего тела.";
    case ThreadState::Blackening:
      return "На Нити проступают тёмные пятна.";
    case ThreadState::Black:
      return "Нить черна. Что-то в тебе называет души пищей.";
  }
  return {};
}

std::string readLine() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    std::exit(EXIT_SUCCESS);
  }
  return line;
}

}  // namespace

ConsoleView::ConsoleView() {
#ifdef _WIN32
  ::SetConsoleOutputCP(CP_UTF8);
  ::SetConsoleCP(CP_UTF8);
#endif
}

void ConsoleView::printSeparator() { std::cout << '\n' << kSeparator << '\n'; }

void ConsoleView::showTitle() const {
  printSeparator();
  std::cout << "                 С Е Р Е Б Р Я Н А Я   Н И Т Ь\n";
  std::cout << "        психологический текстовый квест о возвращении домой\n";
  printSeparator();
  std::cout << "Подсказки: число — выбор, [i] — инвентарь, [s] — состояние.\n";
}

void ConsoleView::showActBanner(const std::string& title) const {
  printSeparator();
  std::cout << "                    " << title << '\n';
  printSeparator();
}

void ConsoleView::showNode(const std::string& text,
                           const Player& player) const {
  printSeparator();
  std::cout << "[ Воля: " << player.will() << '/' << player.maxWill()
            << " | Осознанность: " << player.awareness()
            << " | Натяжение Нити: " << player.tension() << " ]\n";
  std::cout << "~ " << threadStateLabel(player.threadState()) << " ~\n\n";
  std::cout << text << '\n';
}

void ConsoleView::showSystemMessage(const std::string& text) const {
  std::cout << "\n* " << text << '\n';
}

void ConsoleView::showNoteFound(int number) const {
  std::cout << "\n>>> Записка Сновидца №" << number << ": "
            << notes::text(number) << '\n';
}

void ConsoleView::showStatus(const Player& player) const {
  printSeparator();
  std::cout << "Воля: " << player.will() << '/' << player.maxWill() << '\n'
            << "Осознанность: " << player.awareness() << '\n'
            << "Натяжение Нити: " << player.tension() << '\n'
            << "Состояние Нити: " << threadStateLabel(player.threadState())
            << '\n'
            << "Якорей собрано: " << player.anchorCount() << '\n'
            << "Записок Сновидцев: " << player.noteCount() << " из "
            << notes::TOTAL << '\n';
}

void ConsoleView::showChoices(const std::vector<const Choice*>& choices,
                              bool featherActive) const {
  std::cout << '\n';
  for (std::size_t i = 0; i < choices.size(); ++i) {
    std::cout << "  " << (i + 1) << ". " << choices[i]->text();
    if (featherActive && choices[i]->isParasitic()) {
      std::cout << "   [чёрный росчерк Пера]";
    }
    std::cout << '\n';
  }
}

ConsoleView::Input ConsoleView::readInput(std::size_t choiceCount) const {
  while (true) {
    std::cout << "\n> ";
    const std::string line = readLine();
    if (line == "i" || line == "I" || line == "и" || line == "И") {
      return {.kind = Input::Kind::Inventory};
    }
    if (line == "s" || line == "S" || line == "с" || line == "С") {
      return {.kind = Input::Kind::Status};
    }
    try {
      const auto value = static_cast<std::size_t>(std::stoul(line));
      if (value >= 1 && value <= choiceCount) {
        return {.kind = Input::Kind::Choice, .index = value - 1};
      }
    } catch (const std::exception&) {
    }
    std::cout << "Введите число от 1 до " << choiceCount << ", либо [i]/[s].\n";
  }
}

std::size_t ConsoleView::readIndex(std::size_t count) {
  while (true) {
    std::cout << "\n> ";
    const std::string line = readLine();
    try {
      const auto value = static_cast<std::size_t>(std::stoul(line));
      if (value >= 1 && value <= count) {
        return value - 1;
      }
    } catch (const std::exception&) {
    }
    std::cout << "Введите число от 1 до " << count << ".\n";
  }
}

void ConsoleView::showInventory(const Inventory& inventory) const {
  printSeparator();
  std::cout << "Инвентарь (" << inventory.size() << '/' << cfg::inv::SLOTS
            << "):\n";
  if (inventory.isEmpty()) {
    std::cout << "  Пусто. Воспоминания ещё не обрели форму.\n";
    return;
  }
  const auto& items = inventory.items();
  for (std::size_t i = 0; i < items.size(); ++i) {
    std::cout << "  " << (i + 1) << ". " << items[i]->name() << " — "
              << items[i]->description() << '\n';
  }
}

std::optional<std::size_t> ConsoleView::chooseItem(const Inventory& inventory,
                                                   const std::string& prompt,
                                                   bool allowCancel) const {
  std::cout << '\n' << prompt << '\n';
  const std::size_t count = inventory.size();
  if (allowCancel) {
    std::cout << "  0. Назад\n";
  }
  while (true) {
    std::cout << "\n> ";
    const std::string line = readLine();
    try {
      const auto value = static_cast<std::size_t>(std::stoul(line));
      if (allowCancel && value == 0) {
        return std::nullopt;
      }
      if (value >= 1 && value <= count) {
        return value - 1;
      }
    } catch (const std::exception&) {
    }
    std::cout << "Неверный ввод.\n";
  }
}

void ConsoleView::showItemGained(const std::string& itemName) const {
  std::cout << "\n>>> Получен предмет: " << itemName << '\n';
}

void ConsoleView::showItemForgotten(const std::string& itemName) const {
  std::cout << "\n>>> Ты забываешь: " << itemName
            << ". Предмет исчезает навсегда. "
            << "Нить темнеет на один оборот.\n";
}

void ConsoleView::showMimicryTakesControl(const std::string& choiceText) const {
  std::cout
      << "\n!!! Чужая рука поднимается раньше твоей мысли. Мимикри выбирает: «"
      << choiceText << "»\n";
}

void ConsoleView::showCheckpointCreated() const {
  std::cout << "\n>>> Точка якорения создана. Нить запомнила это место.\n";
}

void ConsoleView::showCheckpointReturn() const {
  printSeparator();
  std::cout
      << "Нить лопается... но не до конца. Освящённый осколок вспыхивает,\n"
         "и серебряная леска тянет тебя обратно — к точке якорения.\n";
}

void ConsoleView::showCombatIntro(const Enemy& enemy) const {
  printSeparator();
  std::cout << "БОЙ: " << enemy.name() << '\n';
}

void ConsoleView::showCombatState(const Player& player,
                                  const Enemy& enemy) const {
  std::cout << "\n[" << enemy.name() << " — HP: " << enemy.hp() << "]  "
            << "[Воля: " << player.will() << " | О: " << player.awareness()
            << " | НН: " << player.tension() << "]\n";
}

std::size_t ConsoleView::chooseCombatAction(
    const std::vector<const CombatAction*>& actions) const {
  std::cout << '\n';
  for (std::size_t i = 0; i < actions.size(); ++i) {
    std::cout << "  " << (i + 1) << ". " << actions[i]->name() << '\n';
  }
  return readIndex(actions.size());
}

void ConsoleView::showStatement(std::size_t number,
                                const std::string& text) const {
  printSeparator();
  std::cout << "Утверждение " << number << " из "
            << cfg::finalcfg::STATEMENT_COUNT << ".\n";
  std::cout << "Мимикри: " << text << '\n';
}

AnswerType ConsoleView::readAnswer(
    const std::vector<AnswerType>& answers) const {
  std::cout << '\n';
  for (std::size_t i = 0; i < answers.size(); ++i) {
    std::cout << "  " << (i + 1) << ". " << answerLabel(answers[i]) << '\n';
  }
  return answers[readIndex(answers.size())];
}

void ConsoleView::showFinalChoices(
    const std::vector<const FinalChoice*>& choices) const {
  printSeparator();
  std::cout << "Финальный выбор. За его спиной — твоё тело. За твоей — весь "
               "пройденный путь.\n\n";
  for (std::size_t i = 0; i < choices.size(); ++i) {
    std::cout << "  " << (i + 1) << ". " << choices[i]->text() << '\n';
  }
}

std::size_t ConsoleView::readFinalChoice(std::size_t count) const {
  return readIndex(count);
}

void ConsoleView::showEnding(const std::string& title, const std::string& text,
                             const std::string& epilogue) const {
  printSeparator();
  std::cout << "                    " << title << '\n';
  printSeparator();
  std::cout << text << "\n\nЭПИЛОГ. " << epilogue << '\n';
  printSeparator();
  std::cout << "Конец игры. Спасибо за прохождение «Серебряной нити».\n";
}

}  // namespace st
