#pragma once
#include "Engine/GameObject.h"
#include "Attributes.h"
#include "Animation.h"
#include <vector>

// Forward declaration
class Player;

class Enemy : public GameObject {
public:
    Enemy(GameObject* parent);
   virtual ~Enemy();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // Attribute management
    Attribute* GetActiveAttribute() const;
    void SetAttribute(Attribute* attribute);

    // Combat mechanics
    virtual void AttackPlayer();
    void ReceiveAttack(int damage);

    int GetAttackPower() const;

protected:
    // Attributes
    int health;
    int attackPower;
    int defense;
    float speed;
    Attribute* activeAttribute_;
   enum State {
        Idle_, Run_, Jump_, Attack_, Hit_, Death_, Dodge_, Shoot_, Fall_, Shield_, IdleShield_
    };
    State currentState;
    // AI and state management
    virtual void HandleAI();
    virtual void SetAnimationState(State newState);

 

    // Animation handling
    Animation* baseAnimation;

    // Image handles
    int IdleImg;
    int RunImg;
    int JumpImg;
    int AttackImg;
    int HitImg;
    int DeathImg;

    // AI-specific properties
    float patrolStartX;
    float patrolEndX;
    float chaseDistance;
    float attackRange;
    float shootingRange;
    float shootingCooldown;
    float attackCooldown;
    float attackTimer;

    // Direction handling
    bool facingRight;

    // Player reference
    Player* player;

    // Helper function to check if the player is in range
    bool PlayerInRange();
    bool PlayerInAttackRange();

    // AI behaviors
    void Patrol();
    void Chase(Player& player);
    void Shoot(Player& player);

    // Handling attribute-based attacks
    void PerformAttributeAttack();
};
