#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"
#include "Animation.h"

class AnimalEnemy : public Enemy {
public:
    AnimalEnemy(GameObject* parent);
    ~AnimalEnemy();

    void Initialize() override;
    void Update() override;
    void HandleAI() override;
    void AttackPlayer() override;
    void Draw() override;
    void SetAnimationState(State newState) override;

private:
    // Additional image handles if needed
};
