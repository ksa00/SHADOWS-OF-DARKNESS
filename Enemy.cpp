#include "Enemy.h"
#include "Player.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include <cassert>

Enemy::Enemy(GameObject* parent)
    : GameObject(parent, "Enemy"), health(100), attackPower(10), defense(5), speed(1.0f), attribute(-1), currentState(Idle_), facingRight(true)
{
    baseAnimation = nullptr;
    IdleImg = -1;
    RunImg = -1;
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
    // Load images and initialize animations
    IdleImg = Image::Load("Enemy_Shadow0/Idle.png");
    assert(IdleImg >= 0);
    RunImg = Image::Load("Enemy_Shadow0/Run.png");
    assert(RunImg >= 0);
    AttackImg = Image::Load("Enemy_Shadow0/Attack1.png");
    assert(AttackImg >= 0);
    // HitImg = Image::Load("Enemy_Shadow0/Hit.png");
    // assert(HitImg >= 0);
    DeathImg = Image::Load("Enemy_Shadow0/Death.png");
    assert(DeathImg >= 0);

    // Set initial animation to Idle
    SetPosition({ 600.0f, 500.0f, 0.0f }); // Example position
    baseAnimation = new Animation(32, 64, 6, 0.055f, IdleImg);

    // Initialize AI-specific properties
    patrolStartX = 600.0f; // Example start position for patrolling
    patrolEndX = 800.0f;   // Example end position for patrolling
    chaseDistance = 200.0f; // Example chase distance
    shootingRange = 150.0f; // Example shooting range
    shootingCooldown = 1.0f; // Example shooting cooldown in seconds
}

void Enemy::Update() {
    HandleAI();
    baseAnimation->Update();
    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Enemy::Draw() {
    baseAnimation->Draw(transform_, facingRight); // Use facingRight to determine direction
    for (auto anim : overlayAnimations) {
        anim->Draw(transform_, facingRight);
    }
}

void Enemy::Release() {
    // Release resources
}

int Enemy::GetAttribute() const {
    return attribute;
}

void Enemy::SetAttribute(int newAttribute) {
    attribute = newAttribute;
}

void Enemy::TakeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        SetAnimationState(Death_);
        // Handle enemy death logic, like removing the enemy from the game
    }
    else {
        SetAnimationState(Hit_);
    }
}

void Enemy::Attack(Player& player) {
    int baseDamage = attackPower;
    int finalDamage = baseDamage;

    for (int attr : player.GetActiveAttributes()) {
        if (attribute == ATTR_FIRE && attr == ATTR_WATER) {
            finalDamage /= 2;
        }
        else if (attribute == ATTR_WATER && attr == ATTR_FIRE) {
            finalDamage *= 2;
        }
        // Other attribute interactions...
    }

    if (finalDamage > 0) {
        player.TakeDamage(finalDamage);
    }
}

void Enemy::HandleAI() {
    switch (currentState) {
    case Idle_:
        Patrol();
        break;
    case Run_:
        // Optionally handle run logic separately if needed
        break;
    case Attack_:
        // Optionally handle attack logic separately if needed
        break;
    case Hit_:
        // Optionally handle hit logic separately if needed
        break;
    case Death_:
        // Optionally handle death logic separately if needed
        break;
    }
}
void Enemy::Patrol() {
    Debug::Log("Patrolling. Current position: " + std::to_string(GetPosition().x) + ", Facing right: " + std::to_string(facingRight), true);

    if (facingRight) {
        SetPosition({ GetPosition().x + speed, GetPosition().y, GetPosition().z });
        Debug::Log("Moving right. New position: " + std::to_string(GetPosition().x), true);
        if (GetPosition().x >= patrolEndX) {
            facingRight = false;
            Debug::Log("Reached patrol end. Switching direction to left.", true);
        }
    }
    else {
        SetPosition({ GetPosition().x - speed, GetPosition().y, GetPosition().z });
        Debug::Log("Moving left. New position: " + std::to_string(GetPosition().x), true);
        if (GetPosition().x <= patrolStartX) {
            facingRight = true;
            Debug::Log("Reached patrol start. Switching direction to right.", true);
        }
    }

    Debug::Log("Animation state before setting: " + std::to_string(currentState), true);
    SetAnimationState(Run_);
    Debug::Log("Animation state after setting: " + std::to_string(currentState), true);

    // Add log to confirm direction change and state after movement
    Debug::Log("Current direction after movement: " + std::to_string(facingRight) + ", Position: " + std::to_string(GetPosition().x), true);
}



void Enemy::Chase(Player& player) {
    float distance = player.GetPosition().x - GetPosition().x;
    if (abs(distance) < chaseDistance) {
        if (distance > 0) {
            SetPosition({ GetPosition().x + speed, GetPosition().y, GetPosition().z });
            facingRight = true;
        }
        else {
            SetPosition({ GetPosition().x - speed, GetPosition().y, GetPosition().z });
            facingRight = false;
        }
        SetAnimationState(Run_);
    }
    else {
        SetAnimationState(Idle_);
    }
}

void Enemy::Shoot(Player& player) {
    static float cooldown = 0;
    cooldown -= 1.0f / 60.0f; // Assuming a 60 FPS update rate

    float distance = player.GetPosition().x - GetPosition().x;
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
            baseAnimation->SetAnimation(32, 64, 6, 0.055f, IdleImg);
            break;
        case Run_:
            baseAnimation->SetAnimation(32, 64, 4, 0.075f, RunImg);
            break;
        case Attack_:
            baseAnimation->SetAnimation(137, 40, 8, 0.05f, AttackImg);
            break;
        case Hit_:
            baseAnimation->SetAnimation(48, 48, 4, 0.1f, HitImg);
            break;
        case Death_:
            baseAnimation->SetAnimation(31, 40, 11, 0.12f, DeathImg);
            break;
        }
    }
}
