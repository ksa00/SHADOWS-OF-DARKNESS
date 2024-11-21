#pragma once
#include "Engine/GameObject.h"
#include "Animation.h"
#include"PowerUp.h"
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
    void ApplyPowerUp(int powerUpImageHandle);
    void CollectPowerUp(PowerUp* powerUp);
    void UpdateScore(int points);
    void UpdateLevel(int newLevel);
    const std::string& GetName() const;
    int GetAttribute() const;
    int GetHealth() const;
    int GetScore() const;
    int GetLevel() const;

private:
    enum State {
        Idle_, Run_, Jump_, Fall_, Hit_, Attack_, Dash_, Death_
    };
    void HandleInput();
    void ApplyGravity();
    void CheckLanding();
    void Idle();
    void Run();
    void Jump();
    void Fall();
    void Attack();
    void Dash();
    void Hit(int amount);
    void Death();
    void SetAnimationState(State newState);

    
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
    int Attribute;
    int health;
    int score;
    int level;
    int activePowerUp;
    Animation* baseAnimation;
    std::vector<Animation*> overlayAnimations;
    void SetName(const std::string& playerName);
    void SetHealth(int health);
    void SetAttribute(int handle);
    void SetActivePowerUp(int handle);
    bool isGrounded; // Flag to check if the player is on the ground
    float groundLevel; // Define the ground level
    bool facingRight; // Track the player's direction
    float speed; // Movement speed
    float jumpVelocity; // Track the player's jump velocity
    float jumpForce; // Jump force
    float gravity; // Gravity
    float dashSpeed; // Dash speed
};
