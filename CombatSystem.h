#pragma once
#include "Player.h"
#include "Enemy.h"

class CombatSystem {
public:
    static void PerformAttack(Player* player, Enemy* enemy);
    static void PerformAttack(Enemy* enemy, Player* player);
};
