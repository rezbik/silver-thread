#pragma once

#include <memory>
#include <string>

namespace st {

/// базовый враг
class Enemy {
 public:
  Enemy(std::string name, int hp, std::string attackText,
        std::string defeatText, std::string screamLabel)
      : name_(std::move(name)),
        hp_(hp),
        attackText_(std::move(attackText)),
        defeatText_(std::move(defeatText)),
        screamLabel_(std::move(screamLabel)) {}

  virtual ~Enemy() = default;

  void takeDamage(int amount);
  [[nodiscard]] bool isDefeated() const noexcept { return hp_ <= 0; }
  [[nodiscard]] int hp() const noexcept { return hp_; }
  [[nodiscard]] const std::string& name() const noexcept { return name_; }
  [[nodiscard]] const std::string& attackText() const noexcept {
    return attackText_;
  }
  [[nodiscard]] const std::string& defeatText() const noexcept {
    return defeatText_;
  }
  [[nodiscard]] const std::string& screamLabel() const noexcept {
    return screamLabel_;
  }

 private:
  std::string name_;
  int hp_;
  std::string attackText_;
  std::string defeatText_;
  std::string screamLabel_;
};

/// тень-отголосок (кухн¤, јкт 1)
class ShadowEcho final : public Enemy {
 public:
  ShadowEcho();
};

/// фигура забытого имени (площадь, јкт 2)
class ForgottenNameFigure final : public Enemy {
 public:
  ForgottenNameFigure();
};

/// фабричный метод дл¤ врагов
class EnemyFactory {
 public:
  EnemyFactory() = delete;
  [[nodiscard]] static std::unique_ptr<Enemy> create(
      const std::string& enemyId);
};

namespace enemyid {
inline constexpr std::string_view SHADOW_ECHO = "shadow_echo";
inline constexpr std::string_view FORGOTTEN_FIGURE = "forgotten_figure";
}  // namespace enemyid

}  // namespace st
