#include "st/core/Inventory.hpp"

#include <algorithm>

#include "st/Constants.hpp"

namespace st {

    Inventory::Inventory(const Inventory& other) {
        items_.reserve(other.items_.size());
        for (const auto& item : other.items_) {
            items_.push_back(item->clone());
        }
    }

    Inventory& Inventory::operator=(const Inventory& other) {
        if (this != &other) {
            Inventory copy(other);
            items_ = std::move(copy.items_);
        }
        return *this;
    }

    bool Inventory::isFull() const noexcept {
        return items_.size() >= static_cast<std::size_t>(cfg::inv::SLOTS);
    }

    bool Inventory::isEmpty() const noexcept { return items_.empty(); }

    bool Inventory::contains(const std::string& itemId) const { return find(itemId) != nullptr; }

    std::size_t Inventory::size() const noexcept { return items_.size(); }

    bool Inventory::add(std::shared_ptr<Item> item) {
        if (isFull() || item == nullptr) {
            return false;
        }
        items_.push_back(std::move(item));
        return true;
    }

    std::shared_ptr<Item> Inventory::removeAt(std::size_t index) {
        if (index >= items_.size()) {
            return nullptr;
        }
        auto item = items_[index];
        items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(index));
        return item;
    }

    std::shared_ptr<Item> Inventory::find(const std::string& itemId) const {
        const auto it = std::find_if(items_.begin(), items_.end(),
            [&itemId](const auto& item) { return item->id() == itemId; });
        return it == items_.end() ? nullptr : *it;
    }

    const std::vector<std::shared_ptr<Item>>& Inventory::items() const noexcept { return items_; }

    void Inventory::onActChanged() {
        for (const auto& item : items_) {
            item->onActChanged();
        }
    }

} // namespace st