#pragma once

#include <memory>
#include <string>

#include "st/items/Item.hpp"

namespace st {

/// фабричный метод для создания предметов по идентификатору
class ItemFactory {
 public:
  ItemFactory() = delete;
  [[nodiscard]] static std::shared_ptr<Item> create(const std::string& itemId);
};

}  // namespace st
