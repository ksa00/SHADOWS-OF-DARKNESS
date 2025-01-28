#include "AnimalEnemy.h"
#include "CombatSystem.h"
#include "Player.h"
#include "Engine/Image.h"

AnimalEnemy::AnimalEnemy(GameObject* parent) : Enemy(parent) {
    // Setting specific attributes
    health = 50;
    attackPower = 10;
    patrolStartX = 600.0f;
    patrolEndX = 800.0f;
    chaseDistance = 200.0f;
    attackRange = 50.0f;
    transform_.position_ = { 500.0f, 300.0f, 0.0f }; // Example position
}

AnimalEnemy::~AnimalEnemy() {}

void AnimalEnemy::Initialize() {
    // Load AnimalEnemy-specific images and initialize other properties
    IdleImg = Image::Load("AnimalEnemy/Idle.png");
    RunImg = Image::Load("AnimalEnemy/Walk.png");
    AttackImg = Image::Load("AnimalEnemy/Attack.png");

    // Initialize base animation
    baseAnimation = new Animation(4, 0.1f, IdleImg);

    // Set other initializations
    player = dynamic_cast<Player*>(FindObject("Player"));
}

void AnimalEnemy::Update() {
    HandleAI();
    attackTimer -= 1.0f / 60.0f; // Assuming 60 FPS
    baseAnimation->Update(); // Ensure the animation is updated each frame
}

void AnimalEnemy::HandleAI() {
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

void AnimalEnemy::AttackPlayer() {
    if (attackTimer <= 0.0f) {
        if (player && !player->IsDead()) {
            CombatSystem::PerformAttack(this, player);
            PerformAttributeAttack(); // Apply attribute animation
            SetAnimationState(Attack_);
        }
        attackTimer = attackCooldown;
    }
}

void AnimalEnemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
}

void AnimalEnemy::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(14, 0.08f, IdleImg); // 4 frames, 0.1s duration per frame
            break;
        case Run_:
            baseAnimation->SetAnimation(14, 0.08f, RunImg); // 6 frames, 0.1s duration per frame
            break;
        case Attack_:
            baseAnimation->SetAnimation(9, 0.11f, AttackImg); // 8 frames, 0.1s duration per frame
            break;
        }
    }
}
