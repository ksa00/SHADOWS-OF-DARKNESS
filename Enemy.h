#pragma once

#include "Engine/GameObject.h"
#include "Animation.h"
#include "Attributes.h"
#include <vector>

// Forward declaration
class Player;

class Enemy : public GameObject {
public:
    Enemy(GameObject* parent);
    ~Enemy();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // Attribute management
    int GetAttribute() const;
    void SetAttribute(int attribute);

    // Combat mechanics
    void TakeDamage(int amount);
    void Attack(Player& player);

protected:
    // Attributes
    int health;
    int attackPower;
    int defense;
    int speed;
    int attribute; // Enemy's attribute

    // AI and state management
    void HandleAI();
    enum State {
        Idle_, Run_, Attack_, Hit_, Death_
    };
    State currentState;

    // Animation handling
    void SetAnimationState(State newState);
    Animation* baseAnimation;
    std::vector<Animation*> overlayAnimations;

    // AI-specific properties
    float patrolStartX;
    float patrolEndX;
    float chaseDistance;
    float shootingRange;
    float shootingCooldown;

    // Direction handling
    bool facingRight;

private:
    int IdleImg;
    int RunImg;
    int AttackImg;
    int HitImg;
    int DeathImg;

    // AI behaviors
    void Patrol();
    void Chase(Player& player);
    void Shoot(Player& player);
};
