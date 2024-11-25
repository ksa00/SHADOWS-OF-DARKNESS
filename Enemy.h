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
    Attribute* GetActiveAttribute() const;
    void SetAttribute(Attribute* attribute);

    // Combat mechanics
    void AttackPlayer(); // Use CombatSystem
    void ReceiveAttack(int damage); // Renamed from TakeDamage

    int GetAttackPower() const; // Declare GetAttackPower

protected:
    // Attributes
    int health;
    int attackPower;
    int defense;
    int speed;
    Attribute* activeAttribute_;

    // AI and state management
    void HandleAI();
    enum State {
        Idle_, Run_, Jump_, Attack_, Hit_, Death_
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
    float attackRange;
    float shootingRange;
    float shootingCooldown;
    float attackCooldown; // Add attack cooldown
  float attackTimer; // Add attack timer
    // Direction handling
    bool facingRight;

    // Image handles
    int IdleImg;
    int RunImg;
    int JumpImg;
    int AttackImg;
    int HitImg;
    int DeathImg;

    // Player reference
    Player* player;

    // Helper function to check if the player is in range
    bool PlayerInRange();
    bool PlayerInAttackRange();

    // AI behaviors
    void Patrol();
    void Chase(Player& player);
    void Shoot(Player& player);
};
