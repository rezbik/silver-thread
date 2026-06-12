#pragma once

#include <memory>
#include <string>

namespace st {

class Player;

/// базовый класс астрального предмета
class Item {
 public:
  struct UseResult {
    std::string text;
    bool consecrated{false};
  };

  Item(std::string id, std::string name, std::string description)
      : id_(std::move(id)),
        name_(std::move(name)),
        description_(std::move(description)) {}

  virtual ~Item() = default;

  Item(const Item&) = default;
  Item& operator=(const Item&) = default;
  Item(Item&&) = default;
  Item& operator=(Item&&) = default;

  [[nodiscard]] virtual std::shared_ptr<Item> clone() const = 0;
  virtual UseResult use(Player& player) = 0;
  virtual void onActChanged() {}

  [[nodiscard]] const std::string& id() const noexcept { return id_; }
  [[nodiscard]] const std::string& name() const noexcept { return name_; }
  [[nodiscard]] const std::string& description() const noexcept {
    return description_;
  }

 private:
  std::string id_;
  std::string name_;
  std::string description_;
};

}  // namespace st
