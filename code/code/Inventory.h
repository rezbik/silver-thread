#pragma once

#include <memory>
#include <string>
#include <vector>

// ќпережающее объ¤вление базового класса предмета дл¤ избежани¤ циклической
// зависимости
class Item;

class Inventory {
 private:
  int slots = 4;  // ќграничение инвентар¤ из UML и GDD [cite: 2, 77]
  std::vector<std::shared_ptr<Item>> items;

 public:
  Inventory() = default;

  bool addItem(std::shared_ptr<Item> item);
  void removeItem(std::shared_ptr<Item> item);
  void forgetItem(std::shared_ptr<Item>
                      item);  // »з механики "÷ена воспоминаний" [cite: 77]
  bool isFull() const;
  bool hasItem(const std::string& itemName) const;
  const std::vector<std::shared_ptr<Item>>& getItems() const;
};
