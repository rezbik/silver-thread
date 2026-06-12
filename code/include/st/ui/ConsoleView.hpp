#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include "st/endings/FinalChoice.hpp"
#include "st/endings/Statement.hpp"

namespace st {

class Player;
class Choice;
class Enemy;
class CombatAction;
class Inventory;

/// весь ввод и вывод
class ConsoleView {
 public:
  struct Input {
    enum class Kind { Choice, Inventory, Status };
    Kind kind{Kind::Choice};
    std::size_t index{0};
  };

  ConsoleView();

  void showTitle() const;
  void showActBanner(const std::string& title) const;
  void showNode(const std::string& text, const Player& player) const;
  void showSystemMessage(const std::string& text) const;
  void showNoteFound(int number) const;
  void showStatus(const Player& player) const;

  void showChoices(const std::vector<const Choice*>& choices,
                   bool featherActive) const;
  [[nodiscard]] Input readInput(std::size_t choiceCount) const;

  void showInventory(const Inventory& inventory) const;
  [[nodiscard]] std::optional<std::size_t> chooseItem(
      const Inventory& inventory, const std::string& prompt,
      bool allowCancel) const;
  void showItemGained(const std::string& itemName) const;
  void showItemForgotten(const std::string& itemName) const;

  void showMimicryTakesControl(const std::string& choiceText) const;
  void showCheckpointCreated() const;
  void showCheckpointReturn() const;

  void showCombatIntro(const Enemy& enemy) const;
  void showCombatState(const Player& player, const Enemy& enemy) const;
  [[nodiscard]] std::size_t chooseCombatAction(
      const std::vector<const CombatAction*>& actions) const;

  void showStatement(std::size_t number, const std::string& text) const;
  [[nodiscard]] AnswerType readAnswer(
      const std::vector<AnswerType>& answers) const;
  void showFinalChoices(const std::vector<const FinalChoice*>& choices) const;
  [[nodiscard]] std::size_t readFinalChoice(std::size_t count) const;

  void showEnding(const std::string& title, const std::string& text,
                  const std::string& epilogue) const;

 private:
  [[nodiscard]] static std::size_t readIndex(std::size_t count);
  static void printSeparator();
};

}  // namespace st
