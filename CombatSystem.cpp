#include "CombatSystem.h"

void CombatSystem::PerformAttack(Player* player, Enemy* enemy) {
    if (player && enemy) {
        int baseDamage = player->GetAttackPower();
        int finalDamage = baseDamage;

        for (Attribute* attr : player->GetActiveAttributes()) {
            if (attr->GetType() == Attribute::FIRE && enemy->GetActiveAttribute() && enemy->GetActiveAttribute()->GetType() == Attribute::WATER) {
                finalDamage /= 2;
            }
            else if (attr->GetType() == Attribute::WATER && enemy->GetActiveAttribute() && enemy->GetActiveAttribute()->GetType() == Attribute::FIRE) {
                finalDamage *= 2;
            }
        }

        if (finalDamage > 0) {
            enemy->ReceiveAttack(finalDamage);
        }
    }
}

void CombatSystem::PerformAttack(Enemy* enemy, Player* player) {
    if (enemy && player) {
        if (player->GetHealth()>0)
        player->TakeDamage(enemy->GetAttackPower());
    
    }
}
