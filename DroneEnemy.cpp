#include "DroneEnemy.h"
#include "CombatSystem.h"
#include "Player.h"
#include "Engine/Image.h"

DroneEnemy::DroneEnemy(GameObject* parent) : Enemy(parent), DodgeImg(-1) {
    // Setting specific attributes
    health = 40;
    attackPower = 10;

    // Setting initial position
    transform_.position_ = { 700.0f, 300.0f, 0.0f }; // Example position
}

DroneEnemy::~DroneEnemy() {}

void DroneEnemy::Initialize() {
    // Load DroneEnemy-specific images and initialize other properties
    IdleImg = Image::Load("DroneEnemy/Idle.png");
    RunImg = Image::Load("DroneEnemy/Walk.png"); // Fly forward
    AttackImg = Image::Load("DroneEnemy/Shoot.png");
    DeathImg = Image::Load("DroneEnemy/Death.png");
    HitImg = Image::Load("DroneEnemy/Hit.png");
    DodgeImg = Image::Load("DroneEnemy/Dodge.png");

    // Initialize base animation
    baseAnimation = new Animation(4, 0.1f, IdleImg);

    // Set other initializations
    player = dynamic_cast<Player*>(FindObject("Player"));
}

void DroneEnemy::Update() {
    HandleAI();
    baseAnimation->Update(); // Ensure the animation is updated each frame
}

void DroneEnemy::HandleAI() {
    // Implement DroneEnemy AI logic
    if (PlayerInAttackRange()) {
        AttackPlayer();
    }
    else if (PlayerInRange()) {
        Chase(*player);
        SetAnimationState(Run_);
    }
    else {
        Patrol();
        SetAnimationState(Run_);
    }
}

void DroneEnemy::AttackPlayer() {
    if (attackTimer <= 0.0f) {
        if (player && !player->IsDead()) {
            // Implement shooting logic
            SetAnimationState(Attack_);
        }
        attackTimer = attackCooldown;
    }
}

void DroneEnemy::Dodge() {
    // Implement dodge logic
    SetAnimationState(Hit_);
}

void DroneEnemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
}

void DroneEnemy::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(4, 0.1f, IdleImg); // 4 frames, 0.1s duration per frame
            break;
        case Run_:
            baseAnimation->SetAnimation(6, 0.1f, RunImg); // 6 frames, 0.1s duration per frame
            break;
        case Attack_:
            baseAnimation->SetAnimation(8, 0.1f, AttackImg); // 8 frames, 0.1s duration per frame
            break;
        case Hit_:
            baseAnimation->SetAnimation(4, 0.1f, HitImg); // 4 frames, 0.1s duration per frame
            break;
        case Death_:
            baseAnimation->SetAnimation(6, 0.1f, DeathImg); // 6 frames, 0.1s duration per frame
            break;
         case Dodge_:
            baseAnimation->SetAnimation(4, 0.1f, DodgeImg); // 4 frames, 0.1s duration per frame
            break;
        }
    }
}
