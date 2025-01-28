#include "NinjaEnemy.h"
#include "CombatSystem.h"
#include "Player.h"
#include "Engine/Image.h"

NinjaEnemy::NinjaEnemy(GameObject* parent)
    : Enemy(parent), FallImg(-1), ShieldImg(-1), IdleShieldImg(-1), ShootImg(-1) {
    // Setting specific attributes
    health = 70;
    attackPower = 15;

    // Setting initial position
    transform_.position_ = { 500.0f, 400.0f, 0.0f }; // Example position
}

NinjaEnemy::~NinjaEnemy() {}

void NinjaEnemy::Initialize() {
    // Load NinjaEnemy-specific images and initialize other properties
    IdleImg = Image::Load("NinjaEnemy/Idle.png");
    RunImg = Image::Load("NinjaEnemy/Run.png");
    JumpImg = Image::Load("NinjaEnemy/Jump.png");
    AttackImg = Image::Load("NinjaEnemy/Attack.png");
    DeathImg = Image::Load("NinjaEnemy/Death.png");
    FallImg = Image::Load("NinjaEnemy/Fall.png");
    IdleShieldImg = Image::Load("NinjaEnemy/IdleShield.png");
    //ShootImg = Image::Load("NinjaEnemy/Shoot.png");

    // Initialize base animation
    baseAnimation = new Animation(4, 0.1f, IdleImg);

    // Set other initializations
    player = dynamic_cast<Player*>(FindObject("Player"));
}

void NinjaEnemy::Update() {
    HandleAI();
    baseAnimation->Update(); // Ensure the animation is updated each frame
}

void NinjaEnemy::HandleAI() {
    // Implement NinjaEnemy AI logic
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

void NinjaEnemy::AttackPlayer() {
    if (attackTimer <= 0.0f) {
        if (player && !player->IsDead()) {
            CombatSystem::PerformAttack(this, player);
            PerformAttributeAttack(); // Apply attribute animation
            SetAnimationState(Attack_);
        }
        attackTimer = attackCooldown;
    }
}

void NinjaEnemy::ShootPlayer() {
    if (attackTimer <= 0.0f) {
        if (player && !player->IsDead()) {
            // Implement shooting logic
            SetAnimationState(Shoot_);
        }
        attackTimer = attackCooldown;
    }
}

void NinjaEnemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
}

void NinjaEnemy::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(6, 0.167f, IdleImg); // 6 frames, 0.167s duration per frame
            break;
        case Run_:
            baseAnimation->SetAnimation(4, 0.25f, RunImg); // 4 frames, 0.25s duration per frame
            break;
        case Jump_:
            baseAnimation->SetAnimation(4, 0.25f, JumpImg); // 4 frames, 0.25s duration per frame
            break;
        case Attack_:
            baseAnimation->SetAnimation(8, 0.125f, AttackImg); // 8 frames, 0.125s duration per frame
            break;
        case Death_:
            baseAnimation->SetAnimation(11, 0.09f, DeathImg); // 11 frames, 0.09s duration per frame
            break;
        case Fall_:
            baseAnimation->SetAnimation(4, 0.25f, FallImg); // 4 frames, 0.25s duration per frame
            break;
        case IdleShield_:
            baseAnimation->SetAnimation(20, 0.05f, IdleShieldImg); // 20 frames, 0.05s duration per frame
            break;
    
     
        }
    }
}
