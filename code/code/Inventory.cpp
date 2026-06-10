#pragma once
#include "Inventory.h"

#include <algorithm>

#include "Item.h"

bool Inventory::addItem(std::shared_ptr<Item> item) {
  if (isFull()) return false;
  items.push_back(item);
  return true;
}

void Inventory::removeItem(std::shared_ptr<Item> item) {
  items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Inventory::forgetItem(std::shared_ptr<Item> item) { removeItem(item); }

bool Inventory::isFull() const {
  return items.size() >= static_cast<size_t>(slots);
}

bool Inventory::hasItem(const std::string& itemName) const {
  for (const auto& item : items) {
    if (item && item->getName() == itemName) {
      return true;
    }
  }
  return false;
}

const std::vector<std::shared_ptr<Item>>& Inventory::getItems() const {
  return items;
}
