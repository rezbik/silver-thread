#include "st/items/ItemFactory.hpp"

#include <functional>
#include <stdexcept>
#include <unordered_map>

#include "st/items/Items.hpp"
#include "st/mechanics/Types.hpp"

namespace st {

    std::shared_ptr<Item> ItemFactory::create(const std::string& itemId) {
        static const std::unordered_map<std::string, std::function<std::shared_ptr<Item>()>> registry{
            {std::string(itemsid::MOTHER_CUP), [] { return std::make_shared<MotherCup>(); }},
            {std::string(itemsid::DIARY), [] { return std::make_shared<Diary>(); }},
            {std::string(itemsid::MIRROR_SHARD), [] { return std::make_shared<MirrorShard>(); }},
            {std::string(itemsid::TIN_STAR), [] { return std::make_shared<TinStar>(); }},
            {std::string(itemsid::ARCHIVIST_FEATHER), [] { return std::make_shared<ArchivistFeather>(); }},
            {std::string(itemsid::LIGHTER), [] { return std::make_shared<Lighter>(); }},
        };

        const auto it = registry.find(itemId);
        if (it == registry.end()) {
            throw std::invalid_argument("ItemFactory: неизвестный предмет: " + itemId);
        }
        return it->second();
    }

} // namespace st