#include "st/core/Random.hpp"

namespace st {

    namespace {
        constexpr int kPercentMin = 1;
        constexpr int kPercentMax = 100;
    }

    Random::Random() : engine_(std::random_device{}()) {}

    bool Random::percent(int chancePercent) {
        std::uniform_int_distribution<int> dist(kPercentMin, kPercentMax);
        return dist(engine_) <= chancePercent;
    }

    std::size_t Random::index(std::size_t size) {
        if (size == 0) {
            return 0;
        }
        std::uniform_int_distribution<std::size_t> dist(0, size - 1);
        return dist(engine_);
    }

} // namespace st