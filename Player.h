#pragma once
#include "Engine/GameObject.h"
#include "Animation.h"
#include "PowerUp.h"
#include "Attributes.h"
#include "CombatSystem.h"
#include "Enemy.h"
#include <string>
#include <vector>

class Player : public GameObject {
public:
    Player(GameObject* parent);
    ~Player();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // Power-ups
    void ApplyPowerUp(int powerUpImageHandle);
    void CollectPowerUp(PowerUp* powerUp);

    // Updates
    void UpdateScore(int points);
    void UpdateLevel(int newLevel);

    // Getters
    const std::string& GetName() const;
    Attribute* GetAttribute() const;
    int GetHealth() const;
    int GetScore() const;
    int GetLevel() const;
    int GetAttackPower() const;

    // Setters
    void SetName(const std::string& playerName);
    void SetHealth(int health);

    // Attribute management
    void AddAttribute(Attribute* attribute);
    void SetActiveAttributes(const std::vector<Attribute*>& attributes);
    const std::vector<Attribute*>& GetActiveAttributes() const;

    // Combat mechanics
    void PerformAttack();
    void TakeDamage(int amount);

 // Public states for accessibility
    enum State {
        Idle_=0, Run_, Jump_, Fall_, Hit_, Attack_, Dash_, Death_
    };

    // State management and animations
    void SetAnimationState(State newState);

   
    // Movement and combat methods
    void Run();
    void Jump();
    void Fall();
    void Dash();
    void Death();
    void ApplyGravity();
    void HandleInput();
    void CheckLanding();

    //void Hit();

private:
    State currentState;
    std::string name;
    int IdleImg;
    int RunImg;
    int JumpImg;
    int FallImg;
    int HitImg;
    int AttackImg;
    int DashImg;
    int DeathImg;
    int health;
    int score;
    int level;
    int activePowerUp;
    int attackPower;
    Animation* baseAnimation;
    std::vector<Animation*> overlayAnimations;
    std::vector<Attribute*> activeAttributes;
    std::vector<Attribute*> acquiredAttributes;

    Enemy* enemy;
    bool deathAnimationComplete;
    bool isGrounded;
    float groundLevel;
    bool facingRight;
    float speed;
    float jumpVelocity;
    float jumpForce;
    float gravity;
    float dashSpeed;
    float attackTimer;
    const float attackCooldown;
    float stateCooldown;
};
