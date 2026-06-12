#include "st/core/Player.hpp"

#include <algorithm>

#include "st/Constants.hpp"

namespace st {

    namespace {
        int clamp(int value, int low, int high) { return std::clamp(value, low, high); }
    }

    Player::Player()
        : will_(cfg::res::START_WILL),
        maxWill_(cfg::res::START_MAX_WILL),
        awareness_(cfg::res::START_AWARENESS),
        tension_(cfg::res::START_TENSION),
        darkness_(cfg::res::START_DARKNESS) {
    }

    void Player::modifyWill(int delta) { will_ = clamp(will_ + delta, 0, maxWill_); }

    void Player::modifyMaxWill(int delta) {
        maxWill_ = clamp(maxWill_ + delta, cfg::res::MIN_MAX_WILL, cfg::res::START_MAX_WILL);
        will_ = std::min(will_, maxWill_);
    }

    void Player::modifyAwareness(int delta) {
        awareness_ = clamp(awareness_ + delta, 0, cfg::res::MAX_AWARENESS);
    }

    void Player::modifyTension(int delta) {
        tension_ = clamp(tension_ + delta, 0, cfg::res::RESOURCE_CAP);
    }

    void Player::modifyDarkness(int delta) {
        darkness_ = clamp(darkness_ + delta, 0, cfg::res::RESOURCE_CAP);
    }

    void Player::setAwarenessFloor(int minValue) { awareness_ = std::max(awareness_, minValue); }

    bool Player::isThreadBroken() const noexcept {
        return will_ <= 0 || tension_ >= cfg::thread::TENSION_BREAK;
    }

    ThreadState Player::threadState() const noexcept {
        if (darkness_ >= cfg::thread::DARKNESS_BLACK) {
            return ThreadState::Black;
        }
        if (darkness_ >= cfg::thread::DARKNESS_BLACKENING) {
            return ThreadState::Blackening;
        }
        if (tension_ >= cfg::thread::TENSION_WARNING) {
            return ThreadState::Tense;
        }
        return ThreadState::Silver;
    }

    void Player::addAnchor(const std::string& anchorId) { anchors_.insert(anchorId); }
    bool Player::hasAnchor(const std::string& anchorId) const { return anchors_.contains(anchorId); }
    int Player::anchorCount() const noexcept { return static_cast<int>(anchors_.size()); }

    void Player::addFlag(const std::string& flag) { flags_.insert(flag); }
    bool Player::hasFlag(const std::string& flag) const { return flags_.contains(flag); }

    void Player::addNote(int number) { notes_.insert(number); }
    void Player::removeNote(int number) { notes_.erase(number); }
    bool Player::hasNote(int number) const { return notes_.contains(number); }
    int Player::noteCount() const noexcept { return static_cast<int>(notes_.size()); }

    void Player::addStatus(StatusEffect status, int charges) { statuses_[status] = charges; }
    void Player::removeStatus(StatusEffect status) { statuses_.erase(status); }
    bool Player::hasStatus(StatusEffect status) const { return statuses_.contains(status); }

    void Player::consumeStatusCharge(StatusEffect status) {
        const auto it = statuses_.find(status);
        if (it == statuses_.end() || it->second == cfg::statuscfg::PERMANENT) {
            return;
        }
        if (--it->second <= 0) {
            statuses_.erase(it);
        }
    }

    void Player::registerCorrectFinalAnswer() noexcept { ++correctFinalAnswers_; }

} // namespace st