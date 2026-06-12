#pragma once

#include <map>
#include <set>
#include <string>

#include "st/core/Inventory.hpp"
#include "st/mechanics/Types.hpp"

namespace st {

/// состояние героя: ресурсы, Якоря, флаги, записки, статусы.
class Player {
 public:
  Player();

  // --- Ресурсы ---
  [[nodiscard]] int will() const noexcept { return will_; }
  [[nodiscard]] int maxWill() const noexcept { return maxWill_; }
  [[nodiscard]] int awareness() const noexcept { return awareness_; }
  [[nodiscard]] int tension() const noexcept { return tension_; }
  [[nodiscard]] int darkness() const noexcept { return darkness_; }

  void modifyWill(int delta);
  void modifyMaxWill(int delta);
  void modifyAwareness(int delta);
  void modifyTension(int delta);
  void modifyDarkness(int delta);
  void setAwarenessFloor(int minValue);

  /// Разрыв Нити: Воля <= 0 или Натяжение >= 100.
  [[nodiscard]] bool isThreadBroken() const noexcept;
  [[nodiscard]] ThreadState threadState() const noexcept;

  // --- Якоря ---
  void addAnchor(const std::string& anchorId);
  [[nodiscard]] bool hasAnchor(const std::string& anchorId) const;
  [[nodiscard]] int anchorCount() const noexcept;

  // --- Флаги ---
  void addFlag(const std::string& flag);
  [[nodiscard]] bool hasFlag(const std::string& flag) const;

  // --- Записки Сновидцев ---
  void addNote(int number);
  void removeNote(int number);
  [[nodiscard]] bool hasNote(int number) const;
  [[nodiscard]] int noteCount() const noexcept;

  // --- Статусы ---
  void addStatus(StatusEffect status, int charges);
  void removeStatus(StatusEffect status);
  [[nodiscard]] bool hasStatus(StatusEffect status) const;
  void consumeStatusCharge(StatusEffect status);

  // --- Финал ---
  void registerCorrectFinalAnswer() noexcept;
  [[nodiscard]] int correctFinalAnswers() const noexcept {
    return correctFinalAnswers_;
  }

  // --- Инвентарь ---
  [[nodiscard]] Inventory& inventory() noexcept { return inventory_; }
  [[nodiscard]] const Inventory& inventory() const noexcept {
    return inventory_;
  }

 private:
  int will_;
  int maxWill_;
  int awareness_;
  int tension_;
  int darkness_;
  int correctFinalAnswers_{0};

  Inventory inventory_;
  std::set<std::string> anchors_;
  std::set<std::string> flags_;
  std::set<int> notes_;
  std::map<StatusEffect, int> statuses_;
};

}  // namespace st
