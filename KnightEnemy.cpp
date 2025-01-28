#include "KnightEnemy.h"
#include "CombatSystem.h"
#include "Player.h"
#include "Engine/Image.h"

KnightEnemy::KnightEnemy(GameObject* parent) : Enemy(parent) {
    // Setting specific attributes
    health = 100;
    attackPower = 20;
    patrolStartX = 600.0f;
    patrolEndX = 800.0f;
    chaseDistance = 200.0f;
    attackRange = 50.0f;
    transform_.position_ = { 500.0f, 500.0f, 0.0f }; // Example position
}

KnightEnemy::~KnightEnemy() {}

void KnightEnemy::Initialize() {
    // Load KnightEnemy-specific images and initialize other properties
    IdleImg = Image::Load("KnightEnemy/Idle.png");
    RunImg = Image::Load("KnightEnemy/Run.png");
    JumpImg = Image::Load("KnightEnemy/Jump.png");
    AttackImg = Image::Load("KnightEnemy/Attack.png");
    HitImg = Image::Load("KnightEnemy/Hit.png");

    // Initialize base animation
    baseAnimation = new Animation(4, 0.1f, IdleImg);

    // Set other initializations
    player = dynamic_cast<Player*>(FindObject("Player"));
}

void KnightEnemy::Update() {
    HandleAI();
    attackTimer -= 1.0f / 60.0f; // Assuming 60 FPS
    baseAnimation->Update(); // Ensure the animation is updated each frame
}

void KnightEnemy::HandleAI() {
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

void KnightEnemy::AttackPlayer() {
    if (attackTimer <= 0.0f) {
        if (player && !player->IsDead()) {
            CombatSystem::PerformAttack(this, player);
            PerformAttributeAttack(); // Apply attribute animation
            SetAnimationState(Attack_);
        }
        attackTimer = attackCooldown;
    }
}

void KnightEnemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
}

void KnightEnemy::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(17, 0.588f, IdleImg); // 6 frames, 0.1s duration per frame
            break;
        case Run_:
            baseAnimation->SetAnimation(6, 0.167f, RunImg); // 8 frames, 0.1s duration per frame
            break;
        case Jump_:
            baseAnimation->SetAnimation(6, 0.167f, JumpImg); // 6 frames, 0.1s duration per frame
            break;
        case Attack_:
            baseAnimation->SetAnimation(11, 0.09f, AttackImg); // 10 frames, 0.1s duration per frame
            break;
        case Hit_:
            baseAnimation->SetAnimation(3, 0.3f, HitImg); // 4 frames, 0.1s duration per frame
            break;
        }
    }
}
