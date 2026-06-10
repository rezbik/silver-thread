#include "Enemy.h"

#include <algorithm>

void Enemy::takeDamage(int amount) { health = std::max(0, health - amount); }
