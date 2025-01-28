#include "Player.h"
#include "Camera2D.h"
#include "Enemy.h"
#include "CombatSystem.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Attributes.h"
#include <cassert>

Player::Player(GameObject* parent)
    : GameObject(parent, "Player"),
    currentState(Idle_),
    name(""),
    health(30),
    score(0),
    level(1),
    activePowerUp(-1),
    attackPower(10),
    baseAnimation(nullptr),
    isGrounded(true),
    groundLevel(500.0f),
    facingRight(true),
    speed(5.0f),
    jumpVelocity(0.0f),
    jumpForce(20.0f),
    gravity(1.5f),
    attackTimer(0.0f),
    attackCooldown(0.3f) {
    enemy = nullptr;
    IdleImg = -1;
    RunImg = -1;
    JumpImg = -1;
    FallImg = -1;
    HitImg = -1;
    AttackImg = -1;
    DashImg = -1;
    DeathImg = -1;
    totalDashDistance = 100.0f;
}

Player::~Player() {
    delete baseAnimation;
    for (auto anim : overlayAnimations) {
        delete anim;
    }
}

void Player::Initialize() {
    IdleImg = Image::Load("Player/Idle.png");
    assert(IdleImg >= 0);
    RunImg = Image::Load("Player/Run.png");
    assert(RunImg >= 0);
    JumpImg = Image::Load("Player/Jump.png");
    assert(JumpImg >= 0);
    FallImg = Image::Load("Player/Fall.png");
    assert(FallImg >= 0);
    HitImg = Image::Load("Player/Hit.png");
    assert(HitImg >= 0);
    AttackImg = Image::Load("Player/Attack.png");
    assert(AttackImg >= 0);
    DashImg = Image::Load("Player/Dash.png");
    assert(DashImg >= 0);
    DeathImg = Image::Load("Player/Death_Test.png");
    assert(DeathImg >= 0);

    transform_.position_ = { 50.0f, groundLevel, 0.0f };
    baseAnimation = new Animation(12, 0.055f, IdleImg);
    enemy = dynamic_cast<Enemy*>(FindObject("Enemy"));
}

void Player::Update() {
    static int updateCount = 0;
    updateCount++;

    if (!IsDead()) {
        HandleInput();
        ApplyGravity();
        CheckLanding();

    }


    attackTimer -= 1.0f / 60.0f;
    Debug::Log("Player Update Call #" + std::to_string(updateCount));

    baseAnimation->Update();
    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Player::Draw() {
    
    baseAnimation->Draw(transform_, facingRight);

    for (auto anim : overlayAnimations) {
        anim->Draw(transform_, facingRight);
    }
}

void Player::Release() {
    // Release resources
}

void Player::HandleInput() {
    if (IsDead()) {
        return;
    }

    bool isRunning = Input::IsKey(DIK_A) || Input::IsKey(DIK_D);
    bool isJumping = Input::IsKeyDown(DIK_W);
    bool isDashing = Input::IsKeyDown(DIK_LSHIFT);
    bool isAttacking = Input::IsKey(DIK_SPACE);

    if (isRunning && isJumping) {
        Jump();
        Run();
    }
    else if (isRunning && isDashing) {
        Dash();
    }
    else if (isRunning && isAttacking && attackTimer <= 0.0f) {
        PerformAttack();
        attackTimer = attackCooldown;
        Run();
    }
    else if (isRunning) {
        Run();
    }
    else if (isJumping) {
        Jump();
    }
    else if (isDashing) {
        Dash();
    }
    else if (isAttacking && attackTimer <= 0.0f) {
        PerformAttack();
        attackTimer = attackCooldown;
    }
 else if (isGrounded && currentState != Dash_&&currentState!=Death_&&currentState!=Hit_) {
        SetAnimationState(Idle_);
    }

    if (Input::IsKey(DIK_A)) {
        transform_.position_.x -= speed;
        facingRight = false;
    }
    if (Input::IsKey(DIK_D)) {
        transform_.position_.x += speed;
        facingRight = true;
    }
}

void Player::ApplyGravity() {
    if (!isGrounded) {
        jumpVelocity += gravity;
        transform_.position_.y += jumpVelocity;
    }
}

void Player::CheckLanding() {
    if (!isGrounded && transform_.position_.y >= groundLevel) {
        isGrounded = true;
        transform_.position_.y = groundLevel;
        jumpVelocity = 0.0f;
        SetAnimationState(Fall_);
    }
    else if (isGrounded && transform_.position_.y < groundLevel) {
        isGrounded = false;
    }
}

void Player::SetAnimationState(State newState) {
    if (IsDead()) {
        return;
    }

    if (currentState != newState) {
        currentState = newState;
        Debug::Log("Player is Changing state to " + std::to_string(newState));

        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(12, 0.055f, IdleImg);
            break;
        case Run_:
            baseAnimation->SetAnimation(8, 0.075f, RunImg);
            break;
        case Jump_:
            baseAnimation->SetAnimation(4, 0.15f, JumpImg, 0, false);
            isGrounded = false;
            break;
        case Fall_:
            baseAnimation->SetAnimation(4, 0.1f, FallImg);
            break;
        case Attack_:
            if (!activeAttributes.empty()) {
                activeAttributes.front()->SetAttackAnimation(baseAnimation);
            }
            break;
        case Dash_:
            baseAnimation->SetAnimation(10, 0.1f, DashImg, 0, 5, false); // Using 5 frames for dash animation
            break;
        case Hit_:
            baseAnimation->SetAnimation(4, 0.25f, HitImg, false);
            break;
        case Death_:
            baseAnimation->SetAnimation(10, 0.1f, DeathImg,0,10, false); // Play once, no loop

            break;
        }
    }
}

void Player::Run() {
    SetAnimationState(Run_);
}

void Player::Jump() {
    if (isGrounded) {
        jumpVelocity = -jumpForce;
        isGrounded = false;
        SetAnimationState(Jump_);
    }
}

void Player::Fall() {
    SetAnimationState(Fall_);
}

void Player::Dash() {
    
        SetAnimationState(Dash_);
    float dashMovement = 30.0f;
    Debug::Log("Performing Dash Movement: " + std::to_string(dashMovement));

    if (baseAnimation->IsAnimationComplete()) {
        Debug::Log("Dash animation complete, transitioning to Idle state");
        SetAnimationState(Idle_);
    }
}

void Player::Death() {
    if (currentState != Death_) {
        SetAnimationState(Death_);
    }

    if (baseAnimation->IsAnimationComplete()) {
     
        KillMe();
    }
}


void Player::TakeDamage(int amount) {
    health -= amount;
    if (health > 0) {
        SetAnimationState(Hit_);
    }
    else {
        Death();
    }
}


void Player::PerformAttack() {
    enemy = dynamic_cast<Enemy*>(FindObject("Enemy"));
    if (enemy) {
        CombatSystem::PerformAttack(this, enemy);
    }
}

const std::string& Player::GetName() const {
    return name;
}

Attribute* Player::GetAttribute() const {
    if (!acquiredAttributes.empty()) {
        return acquiredAttributes.front();
    }
    return nullptr;
}

int Player::GetHealth() const {
    return health;
}

int Player::GetScore() const {
    return score;
}

int Player::GetLevel() const {
    return level;
}

int Player::GetAttackPower() const {
    return attackPower;
}

void Player::SetName(const std::string& playerName) {
    name = playerName;
}

void Player::SetHealth(int newHealth) {
    health = newHealth;
}

void Player::AddAttribute(Attribute* attribute) {
    acquiredAttributes.push_back(attribute);
}

void Player::SetActiveAttributes(const std::vector<Attribute*>& attributes) {
    activeAttributes = attributes;
}

const std::vector<Attribute*>& Player::GetActiveAttributes() const {
    return activeAttributes;
}

void Player::ApplyPowerUp(int powerUpImageHandle) {
    activePowerUp = powerUpImageHandle;
    // Logic to apply power-up effects
}

void Player::CollectPowerUp(PowerUp* powerUp) {
    ApplyPowerUp(powerUp->GetImageHandle());
}

void Player::UpdateScore(int points) {
    score += points;
}

void Player::UpdateLevel(int newLevel) {
    level = newLevel;
}
