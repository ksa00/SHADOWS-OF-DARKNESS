#include "Enemy.h"
#include "Player.h"
#include "CombatSystem.h"
#include "Engine/Debug.h"
#include <cassert>

Enemy::Enemy(GameObject* parent)
    : GameObject(parent, "Enemy"), health(100), attackPower(10), defense(5), speed(1.0f), activeAttribute_(nullptr), currentState(Idle_), facingRight(true), player(nullptr),
    attackCooldown(1.0f), attackTimer(0.0f), patrolStartX(0.0f), patrolEndX(0.0f), chaseDistance(0.0f), attackRange(0.0f), shootingRange(0.0f), shootingCooldown(0.0f),
    baseAnimation(nullptr), IdleImg(-1), RunImg(-1), JumpImg(-1), AttackImg(-1), HitImg(-1), DeathImg(-1) {}

Enemy::~Enemy() {
    delete baseAnimation;
}

void Enemy::Initialize() {
    // Default initialization logic for all enemies
    currentState = Idle_;
    facingRight = true;
    player = dynamic_cast<Player*>(FindObject("Player"));
}

void Enemy::Update() {
    HandleAI();
    attackTimer -= 1.0f / 60.0f; // Assuming 60 FPS
    baseAnimation->Update(); // Ensure the animation is updated each frame
}

void Enemy::Draw() {
    baseAnimation->Draw(transform_, facingRight);
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

void Enemy::ReceiveAttack(int damage) {
    health -= damage;
    if (health <= 0) {
        SetAnimationState(Death_);
        // Handle animation completion in derived classes if needed
    }
    else {
        SetAnimationState(Hit_);
    }
}

int Enemy::GetAttackPower() const {
    return attackPower;
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
    }
}

void Enemy::Shoot(Player& player) {
    // Implement shooting logic
}

void Enemy::PerformAttributeAttack() {
    if (activeAttribute_) {
        activeAttribute_->SetAttackAnimation(baseAnimation);
    }
}

void Enemy::HandleAI() {
    // Default AI logic, can be overridden in derived classes
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

void Enemy::SetAnimationState(State newState) {
    // Default implementation, can be overridden in derived classes
    if (currentState != newState) {
        currentState = newState;
        // Handle state change logic if needed in the base class
    }
}

void Enemy::AttackPlayer() {
    // Default implementation, can be overridden in derived classes
    if (attackTimer <= 0.0f) {
        player = dynamic_cast<Player*>(FindObject("Player"));  // Ensure player is retrieved
        if (player && !player->IsDead()) {  // Check if player is not dead
            CombatSystem::PerformAttack(this, player);  // Use CombatSystem to handle the attack
        }
        attackTimer = attackCooldown;  // Reset attack timer
    }
}
