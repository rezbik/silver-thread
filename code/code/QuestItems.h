#pragma once

#include "Item.h"

// 1. Чашка матери восстанавливает волю, но увеличивает натяжение
// (воспоминания ранят)
class MotherCup : public Item {
 public:
  MotherCup();
  void use(Player& player) override;
};

// 2. Дневник дает большой буст к ќсознанности
class Diary : public Item {
 public:
  Diary();
  void use(Player& player) override;
};

// 3. Осколок зеркала позволяет создать якори
class MirrorShard : public Item {
 public:
  MirrorShard();
  void use(Player& player) override;
};
// 4. Жестяная звезда предмет защиты, снижает натяжение нити
class TinStar : public Item {
 public:
  TinStar();
  void use(Player& player) override;
};

// 5. Перо архивиста раскрывает скрытые проходы (флаги)
class ArchivistFeather : public Item {
 public:
  ArchivistFeather();
  void use(Player& player) override;
};
