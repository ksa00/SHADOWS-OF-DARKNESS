#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"
#include "Animation.h"

class NinjaEnemy : public Enemy {
public:
    NinjaEnemy(GameObject* parent);
    ~NinjaEnemy();

    void Initialize() override;
    void Update() override;
    void HandleAI() override;
    void AttackPlayer() override;
    void ShootPlayer(); // Special shooting attack
    void Draw() override;
    void SetAnimationState(State newState) override;

private:
    // Additional image handles
    int FallImg;
    int ShieldImg;
    int IdleShieldImg;
    int ShootImg;
};
