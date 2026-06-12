#pragma once

#include <cstddef>
#include <random>

namespace st {

/// источник случайности (для Game и Combat)
class Random {
 public:
  Random();

  [[nodiscard]] bool percent(int chancePercent);

  [[nodiscard]] std::size_t index(std::size_t size);

 private:
  std::mt19937 engine_;
};

}  // namespace st
