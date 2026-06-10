#include "Player.h"

#include <algorithm>
#include <iostream>

void Player::modifyResource(ResourceType type, int value) {
  switch (type) {
    case ResourceType::WILL:
      will = std::clamp(will + value, 0, maxWill);
      break;
    case ResourceType::AWARENESS:
      awareness = std::max(0, awareness + value);
      break;
    case ResourceType::THREAD_TENSION:
      threadTension = std::max(0, threadTension + value);
      break;
    case ResourceType::THREAD_DARKNESS:
      threadDarkness = std::max(0, threadDarkness + value);
      break;
  }
}

bool Player::checkCriticalState() {
  // Если Воля упала до 0 это конец игры
  if (will <= 0) {
    return true;
  }
  return false;
}

void Player::addAnchor(const Anchor& anchor) { anchors.push_back(anchor); }
void Player::addNote(const DreamerNote& note) { notes.push_back(note); }
void Player::addFlag(const std::string& flag) { flags.insert(flag); }
bool Player::hasFlag(const std::string& flag) const {
  return flags.count(flag) > 0;
}
bool Player::hasStatus(const std::string& status) const {
  return std::find(statuses.begin(), statuses.end(), status) != statuses.end();
}
void Player::addStatus(const std::string& status) {
  statuses.push_back(status);
}
