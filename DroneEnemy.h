#pragma once
#include "Engine/GameObject.h"
#include "Enemy.h"
#include "Animation.h"

class DroneEnemy : public Enemy {
public:
    DroneEnemy(GameObject* parent);
    ~DroneEnemy();

    void Initialize() override;
    void Update() override;
    void HandleAI() override;
    void AttackPlayer() override;
    void Dodge(); // Dodge attack
    void Draw() override;
    void SetAnimationState(State newState) override;

private:
    // Additional image handles
    int DodgeImg;
};
