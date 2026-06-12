#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "st/items/Item.hpp"

namespace st {

class Inventory {
 public:
  Inventory() = default;

  Inventory(const Inventory& other);
  Inventory& operator=(const Inventory& other);
  Inventory(Inventory&&) noexcept = default;
  Inventory& operator=(Inventory&&) noexcept = default;
  ~Inventory() = default;

  [[nodiscard]] bool isFull() const noexcept;
  [[nodiscard]] bool isEmpty() const noexcept;
  [[nodiscard]] bool contains(const std::string& itemId) const;
  [[nodiscard]] std::size_t size() const noexcept;

  bool add(std::shared_ptr<Item> item);
  std::shared_ptr<Item> removeAt(std::size_t index);
  [[nodiscard]] std::shared_ptr<Item> find(const std::string& itemId) const;
  [[nodiscard]] const std::vector<std::shared_ptr<Item>>& items()
      const noexcept;

  void onActChanged();

 private:
  std::vector<std::shared_ptr<Item>> items_;
};

}  // namespace st
