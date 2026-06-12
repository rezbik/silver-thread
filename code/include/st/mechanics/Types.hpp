#pragma once

#include <array>
#include <string_view>

namespace st {

/// стадии игры
enum class ActStage { Prologue, Act1, Act2, Act3, Ending };

/// состояния нити
enum class ThreadState { Silver, Tense, Blackening, Black };

/// статусные эффекты игрока
enum class StatusEffect { Blindness, AlienHand, MimicryControl, Exhaustion };

/// идентификаторы якорей
namespace anchors {
inline constexpr std::string_view CUP = "anchor_cup";
inline constexpr std::string_view DIARY = "anchor_diary";
inline constexpr std::string_view MIRROR = "anchor_mirror";
}  // namespace anchors

/// сюжетные флаги
namespace flags {
inline constexpr std::string_view KNOW_THREAD = "know_thread";
inline constexpr std::string_view KNOW_MIMICRY = "know_mimicry";
inline constexpr std::string_view ABSORPTION_PATH = "absorption_path";
inline constexpr std::string_view BATHROOM_CLOSED = "bathroom_closed";
inline constexpr std::string_view MIMICRY_SLOWED = "mimicry_slowed";
inline constexpr std::string_view DOPPEL_TRUTH = "doppel_truth";
inline constexpr std::string_view SHADOW_NAMED = "shadow_named";
inline constexpr std::string_view TWIST_READ = "twist_read";
inline constexpr std::string_view KNOW_NO_DESTROY = "know_cannot_destroy";
inline constexpr std::string_view PAGE_STOLEN = "page_stolen";
inline constexpr std::string_view SQUARE_DONE = "square_done";
inline constexpr std::string_view BRIDGE_DONE = "bridge_done";
inline constexpr std::string_view CAROUSEL_DONE = "carousel_done";
inline constexpr std::string_view CHILDREN_FREED = "children_freed";
inline constexpr std::string_view CHILDREN_CONSUMED = "children_consumed";
inline constexpr std::string_view ECHO_SAVED = "echo_saved";
inline constexpr std::string_view ECHO_CONSUMED = "echo_consumed";
inline constexpr std::string_view ECHO_LEFT = "echo_left";
inline constexpr std::string_view ECHO_DESTROYED = "echo_destroyed";
inline constexpr std::string_view VISITED_SQUARE = "visited_square";
inline constexpr std::string_view VISITED_LIBRARY = "visited_library";
inline constexpr std::string_view VISITED_BRIDGE = "visited_bridge";
inline constexpr std::string_view VISITED_CAROUSEL = "visited_carousel";
}  // namespace flags

/// идентификаторы предметов
namespace itemsid {
inline constexpr std::string_view MOTHER_CUP = "mother_cup";
inline constexpr std::string_view DIARY = "diary";
inline constexpr std::string_view MIRROR_SHARD = "mirror_shard";
inline constexpr std::string_view TIN_STAR = "tin_star";
inline constexpr std::string_view ARCHIVIST_FEATHER = "archivist_feather";
inline constexpr std::string_view LIGHTER = "lighter";
}  // namespace itemsid

/// записки сновидцев
namespace notes {
inline constexpr int TOTAL = 6;
inline constexpr std::array<std::string_view, TOTAL> TEXTS{
    "«Они приходят, когда ты молчишь слишком долго».",
    "«Я думал, я один. Но он со мной с пяти лет».",
    "«Архивариус — бывший спящий. Он не вернулся».",
    "«Чёрная река — это слёзы, которые мы не плакали».",
    "«Дети — это мы. Все мы дети, которых не услышали».",
    "«Скажи это сейчас. Завтра не будет».",
};
inline std::string_view text(int number) {
  return TEXTS.at(static_cast<std::size_t>(number - 1));
}
}  // namespace notes

}  // namespace st
