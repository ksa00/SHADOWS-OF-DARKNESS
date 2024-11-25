#include "Enemy.h"
#include "Player.h"
#include "CombatSystem.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Attributes.h"
#include <cassert>

Enemy::Enemy(GameObject* parent)
    : GameObject(parent, "Enemy"), health(100), attackPower(10), defense(5), speed(1.0f), activeAttribute_(nullptr), currentState(Idle_), facingRight(true), player(nullptr),
    attackCooldown(1.0f), // Set attack cooldown (1 second)
    attackTimer(0.0f) // Initialize attack timer
{
    baseAnimation = nullptr;
    IdleImg = -1;
    RunImg = -1;
    JumpImg = -1;
    AttackImg = -1;
    HitImg = -1;
    DeathImg = -1;
}

Enemy::~Enemy() {
    delete baseAnimation;
    for (auto anim : overlayAnimations) {
        delete anim;
    }
}

void Enemy::Initialize() {
    IdleImg = Image::Load("Enemy_Shadow0/Idle.png");
    assert(IdleImg >= 0);
    RunImg = Image::Load("Enemy_Shadow0/Run.png");
    assert(RunImg >= 0);
    JumpImg = Image::Load("Enemy_Shadow0/Jump.png");
    assert(JumpImg >= 0);
    AttackImg = Image::Load("Enemy_Shadow0/Attack1.png");
    assert(AttackImg >= 0);
  //  HitImg = Image::Load("Enemy_Shadow0/Hit.png");
    //assert(HitImg >= 0);
    DeathImg = Image::Load("Enemy_Shadow0/Death.png");
    assert(DeathImg >= 0);

    transform_.position_ = { 600.0f, 500.0f, 0.0f };
    baseAnimation = new Animation(32, 64, 6, 0.1f, IdleImg);

    patrolStartX = 600.0f;
    patrolEndX = 800.0f;
    chaseDistance = 200.0f;
    attackRange = 50.0f;
    shootingRange = 150.0f;
    shootingCooldown = 1.0f;

    player = dynamic_cast<Player*>(FindObject("Player"));
}

void Enemy::Update() {
    HandleAI();
    attackTimer -= 1.0f / 60.0f; // Assuming 60 FPS

    baseAnimation->Update();
    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Enemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
    for (auto anim : overlayAnimations) {
        anim->Draw(transform_, facingRight);
    }
}

void Enemy::Release() {
    // Release resources
}

Attribute* Enemy::GetActiveAttribute() const {
    return activeAttribute_;
}

void Enemy::SetAttribute(Attribute* attribute) {
    activeAttribute_ = attribute;
}

bool Enemy::PlayerInRange() {
    if (player) {
        float distance = player->GetPosition().x - transform_.position_.x;
        return abs(distance) < chaseDistance;
    }
    return false;
}

bool Enemy::PlayerInAttackRange() {
    if (player) {
        float distance = player->GetPosition().x - transform_.position_.x;
        return abs(distance) < attackRange;
    }
    return false;
}

void Enemy::ReceiveAttack(int damage) {
    health -= damage;
    if (health <= 0) {
        KillMe();  // Set the enemy as dead
        SetAnimationState(Death_);
    }
    else {
      //  Hit();
    }
}

void Enemy::AttackPlayer() {
    if (attackTimer <= 0.0f) {
        player = dynamic_cast<Player*>(FindObject("Player"));  // Ensure player is retrieved
        if (player && !player->IsDead()) {  // Check if player is not dead
            CombatSystem::PerformAttack(this, player);  // Use CombatSystem to handle the attack
        }
        attackTimer = attackCooldown;  // Reset attack timer
    }
}

void Enemy::HandleAI() {
    if (PlayerInAttackRange()) {
        AttackPlayer();
    }
    else if (PlayerInRange()) {
        Chase(*player);
    }
    else {
        Patrol();
    }
}

void Enemy::Chase(Player& player) {
    float distance = player.GetPosition().x - transform_.position_.x;
    if (abs(distance) < chaseDistance) {
        if (distance > 0) {
            transform_.position_.x += speed;
            facingRight = true;
        }
        else {
            transform_.position_.x -= speed;
            facingRight = false;
        }
        SetAnimationState(Run_);
    }
    else {
        SetAnimationState(Idle_);
    }
}

void Enemy::Patrol() {
    if (facingRight) {
        transform_.position_.x += speed;
        if (transform_.position_.x >= patrolEndX) {
            facingRight = false;
        }
    }
    else {
        transform_.position_.x -= speed;
        if (transform_.position_.x <= patrolStartX) {
            facingRight = true;
        }
    }
    SetAnimationState(Run_);
}

void Enemy::Shoot(Player& player) {
    static float cooldown = 0;
    cooldown -= 1.0f / 60.0f; // Assuming a 60 FPS update rate

    float distance = player.GetPosition().x - transform_.position_.x;
    if (abs(distance) < shootingRange && cooldown <= 0) {
        // Fire projectile logic
        // Example: Create a projectile and set its direction towards the player
        cooldown = shootingCooldown; // Reset cooldown
        SetAnimationState(Attack_);
    }
    else {
        SetAnimationState(Idle_);
    }
}


void Enemy::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;

        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(32, 64, 6, 0.1f, IdleImg);
            break;
        case Run_:
            baseAnimation->SetAnimation(32, 64, 4, 0.08f, RunImg);
            break;
        case Attack_:
            if (activeAttribute_) {
                activeAttribute_->SetAttackAnimation(baseAnimation);
            }
            break;
        case Hit_:
            baseAnimation->SetAnimation(48, 48, 4, 0.12f, HitImg);
            break;
        case Death_:
            baseAnimation->SetAnimation(256, 30, 11, 0.15f, DeathImg, false); // Play once, no loop
            break;
        }
    }
}

int Enemy::GetAttackPower() const {
    return attackPower;
}
