#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"
#include "Animation.h"

class KnightEnemy : public Enemy {
public:
    KnightEnemy(GameObject* parent);
    ~KnightEnemy();

    void Initialize() override;
    void Update() override;
    void HandleAI() override;
    void AttackPlayer() override;
    void Draw() override;
    void SetAnimationState(State newState) override;
};
