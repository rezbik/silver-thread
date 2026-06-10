#include "QuestItems.h"

#include <iostream>

#include "Player.h"

// Реализация Чашки Матери
MotherCup::MotherCup()
    : Item("Чашка Матери",
           "Старая фарфоровая чашка с трещиной. Пахнет сушеной липой.", true) {}
void MotherCup::use(Player& player) {
  std::cout << "\n[Вы делаете глоток из пустой чашки. На мгновение "
               "возвращается тепло дома...]\n";
  player.modifyResource(ResourceType::WILL, 30);
  player.modifyResource(ResourceType::THREAD_TENSION, 10);
}

// Реализация Дневника
Diary::Diary::Diary()
    : Item("Потертый Дневник",
           "Твои собственные записи, сделанные незадолго до Комы.", false) {}
void Diary::use(Player& player) {
  if (!player.hasFlag("read_diary")) {
    std::cout << "\n[Вы читаете строки, написанные собственным почерком. "
                 "Осознанность растет.]\n";
    player.modifyResource(ResourceType::AWARENESS, 20);
    player.addFlag("read_diary");
  } else {
    std::cout << "\n[Вы уже изучили эти записи. Но они по-прежнему удерживают "
                 "ваш разум в реальности.]\n";
  }
}

// Реализация Осколка зеркала
MirrorShard::MirrorShard()
    : Item("Осколок зеркала",
           "В нем отражается не комната, а то, что находится глубоко внутри "
           "тебя.",
           true) {}
void MirrorShard::use(Player& player) {
  std::cout << "\n[Вы концентрируетесь на осколке. Пространство вокруг "
               "стабилизируется. Создан Якорь.]\n";
  Anchor newAnchor{"Освященное место", 1, "Якорь, созданный с помощью зеркала"};
  player.addAnchor(newAnchor);
}
// Реализация Жестяной звезды
TinStar::TinStar()
    : Item("Жестяная звезда",
           "Старая детская игрушка. Напоминает о временах, когда ты чувствовал "
           "себя в безопасности.",
           true) {}
void TinStar::use(Player& player) {
  std::cout << "\n[Вы сжимаете звезду в ладони. Натяжение Серебряной нити "
               "ослабевает.]\n";
  player.modifyResource(ResourceType::THREAD_TENSION, -25);
}

// Реализация Пера Архивиста
ArchivistFeather::ArchivistFeather()
    : Item("Перо Архивиста",
           "Невесомое перо, покрытое светящимися чернилами Лимба.", false) {}
void ArchivistFeather::use(Player& player) {
  std::cout << "\n[Вы проводите пером по воздуху. Тайные знаки астрала "
               "становятся видимыми.]\n";
  player.addFlag("knows_secret_paths");
  player.modifyResource(ResourceType::AWARENESS, 10);
}
