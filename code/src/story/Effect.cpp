#include "st/story/Effect.hpp"

#include "st/core/Player.hpp"

namespace st {

Effect& Effect::will(int delta) {
  will_ += delta;
  return *this;
}
Effect& Effect::awareness(int delta) {
  awareness_ += delta;
  return *this;
}
Effect& Effect::tension(int delta) {
  tension_ += delta;
  return *this;
}
Effect& Effect::darkness(int delta) {
  darkness_ += delta;
  return *this;
}
Effect& Effect::maxWill(int delta) {
  maxWill_ += delta;
  return *this;
}
Effect& Effect::floorAwareness(int minValue) {
  awarenessFloor_ = minValue;
  return *this;
}

Effect& Effect::addFlag(std::string_view flag) {
  flags_.emplace_back(flag);
  return *this;
}
Effect& Effect::addAnchor(std::string_view anchorId) {
  anchors_.emplace_back(anchorId);
  return *this;
}
Effect& Effect::addNote(int number) {
  notesAdded_.push_back(number);
  return *this;
}
Effect& Effect::removeNote(int number) {
  notesRemoved_.push_back(number);
  return *this;
}

Effect& Effect::addStatus(StatusEffect status, int charges) {
  statusesAdded_.emplace_back(status, charges);
  return *this;
}

Effect& Effect::removeStatus(StatusEffect status) {
  statusesRemoved_.push_back(status);
  return *this;
}

Effect& Effect::giveItem(std::string_view itemId) {
  items_.emplace_back(itemId);
  return *this;
}
Effect& Effect::message(std::string text) {
  message_ = std::move(text);
  return *this;
}

Effect& Effect::when(Requirement condition, Effect effect) {
  conditionals_.emplace_back(std::move(condition),
                             std::make_shared<const Effect>(std::move(effect)));
  return *this;
}

void Effect::apply(Player& player, bool softenWhisper,
                   std::vector<std::string>* messagesOut) const {
  if (!message_.empty() && messagesOut != nullptr) {
    messagesOut->push_back(message_);
  }

  int awarenessDelta = awareness_;
  if (softenWhisper && awarenessDelta < 0) {
    awarenessDelta /= cfg::itemcfg::CUP_WHISPER_DIVISOR;
  }

  player.modifyMaxWill(maxWill_);
  player.modifyWill(will_);
  player.modifyAwareness(awarenessDelta);
  player.modifyTension(tension_);
  player.modifyDarkness(darkness_);

  for (const auto& flag : flags_) {
    player.addFlag(flag);
  }
  for (const auto& anchor : anchors_) {
    player.addAnchor(anchor);
  }
  for (const int note : notesAdded_) {
    player.addNote(note);
  }
  for (const int note : notesRemoved_) {
    player.removeNote(note);
  }
  for (const auto& [status, charges] : statusesAdded_) {
    player.addStatus(status, charges);
  }
  for (const auto status : statusesRemoved_) {
    player.removeStatus(status);
  }
  if (awarenessFloor_.has_value()) {
    player.setAwarenessFloor(*awarenessFloor_);
  }

  for (const auto& [condition, effect] : conditionals_) {
    if (condition.check(player)) {
      effect->apply(player, false, messagesOut);
    }
  }
}

}  // namespace st
