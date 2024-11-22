#include "Player.h"
#include "Enemy.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include <cassert>

Player::Player(GameObject* parent)
    : GameObject(parent, "Player"),
    name(""),
    health(100),
    score(0),
    level(1),
    activePowerUp(-1),
    attackPower(10), // Initialize attack power
    baseAnimation(nullptr),
    currentState(Idle_),
    isGrounded(true), // Initialize player as grounded
    groundLevel(500.0f), // Define the ground level
    facingRight(true), // Initialize facing direction
    speed(5.0f), // Initial speed
    jumpVelocity(0.0f), // Initial jump velocity
    jumpForce(20.0f), // Increased jump force for higher jumps
    gravity(1.5f), // Increased gravity for faster falls
    dashSpeed(20.0f) // Increased dash speed for farther dashes
{
    IdleImg = -1;
    RunImg = -1;
    JumpImg = -1;
    FallImg = -1;
    HitImg = -1;
    AttackImg = -1;
    DashImg = -1;
    DeathImg = -1;

    activeAttributes.push_back(ATTR_FIRE); // Starting attribute
}

Player::~Player() {
    delete baseAnimation;
    for (auto anim : overlayAnimations) {
        delete anim;
    }
}

void Player::Initialize() {
    // Load all images during initialization
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
    DeathImg = Image::Load("Player/Death.png");
    assert(DeathImg >= 0);

    // Set initial animation to Idle
    SetPosition({ 50.0f, groundLevel, 0.0f });
    baseAnimation = new Animation(48, 48, 12, 0.055f, IdleImg);
}

void Player::Update() {
    HandleInput();
    ApplyGravity();
    CheckLanding();

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
    // Placeholder input checks; adjust these based on your input system

    bool isRunning = Input::IsKey(DIK_A) || Input::IsKey(DIK_D);
    bool isJumping = Input::IsKeyDown(DIK_W);
    bool isDashing = Input::IsKeyDown(DIK_LSHIFT);
    bool isAttacking = Input::IsKeyDown(DIK_SPACE);

    if (isRunning && isJumping) {
        Jump();
        Run();
    }
    else if (isRunning && isDashing) {
        Dash();
        Run();
    }
    else if (isRunning && isAttacking) {
        Attack();
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
    else if (isAttacking) {
        Attack();
    }
    else if (isGrounded) {
        SetAnimationState(Idle_);
    }

    // Apply movement
    if (Input::IsKey(DIK_A)) {
        SetPosition({ GetPosition().x - speed, GetPosition().y, GetPosition().z });
        facingRight = false;
    }
    if (Input::IsKey(DIK_D)) {
        SetPosition({ GetPosition().x + speed, GetPosition().y, GetPosition().z });
        facingRight = true;
    }
}

void Player::ApplyGravity() {
    // Apply gravity if not grounded
    if (!isGrounded) {
        jumpVelocity += gravity;
        SetPosition({ GetPosition().x, GetPosition().y + jumpVelocity, GetPosition().z });
    }
}

void Player::CheckLanding() {
    // Check if the player is landing on the ground
    if (!isGrounded && GetPosition().y >= groundLevel) {
        isGrounded = true;
        SetPosition({ GetPosition().x, groundLevel, GetPosition().z }); // Ensure player doesn't fall through the ground
        jumpVelocity = 0.0f;
        SetAnimationState(Fall_);
    }
    else if (isGrounded && GetPosition().y < groundLevel) {
        isGrounded = false;
    }
}

void Player::SetAnimationState(State newState) {
    if (currentState != newState) {
        currentState = newState;

        switch (newState) {
        case Idle_:
            baseAnimation->SetAnimation(48, 48, 12, 0.055f, IdleImg);
            break;
        case Run_:
            baseAnimation->SetAnimation(48, 48, 8, 0.075f, RunImg); // Adjusted frame time
            break;
        case Jump_:
            baseAnimation->SetAnimation(48, 48, 4, 0.15f, JumpImg); // Adjusted frame time
            isGrounded = false; // Player is now in the air
            break;
        case Fall_:
            baseAnimation->SetAnimation(48, 48, 4, 0.1f, FallImg); // Adjusted frame time for quicker fall
            break;
        case Attack_:
            baseAnimation->SetAnimation(128, 58, 16, 0.05f, AttackImg); // Adjusted frame dimensions and time
            break;
        case Dash_:
            baseAnimation->SetAnimation(112, 56, 5, 0.07f, DashImg); // Adjusted frame time
            break;
        case Hit_:
            baseAnimation->SetAnimation(48, 48, 4, 0.1f, HitImg); // Adjusted frame time
            break;
        case Death_:
            baseAnimation->SetAnimation(76, 48, 10, 0.12f, DeathImg); // Adjusted frame time
            break;
        }
    }
}

void Player::Run() {
    SetAnimationState(Run_);
}

void Player::Jump() {
    if (isGrounded) {
        jumpVelocity = -jumpForce; // Initial jump velocity
        isGrounded = false;
        SetAnimationState(Jump_);
    }
}

void Player::Fall() {
    SetAnimationState(Fall_);
}

void Player::Attack() {
    // Move the player forward a certain distance when attacking
    float attackMoveDistance = 10.0f; // Adjust the distance as needed
    if (facingRight) {
        SetPosition({ GetPosition().x + attackMoveDistance, GetPosition().y, GetPosition().z });
    }
    else {
        SetPosition({ GetPosition().x - attackMoveDistance, GetPosition().y, GetPosition().z });
    }
    SetAnimationState(Attack_);
}

void Player::Dash() {
    if (facingRight) {
        SetPosition({ GetPosition().x + dashSpeed, GetPosition().y, GetPosition().z });
    }
    else {
        SetPosition({ GetPosition().x - dashSpeed, GetPosition().y, GetPosition().z });
    }
    SetAnimationState(Dash_);
}

void Player::Hit(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    SetAnimationState(Hit_);
}

void Player::ApplyPowerUp(int powerUpImageHandle) {
    activePowerUp = powerUpImageHandle;
}

void Player::CollectPowerUp(PowerUp* powerUp) {
    ApplyPowerUp(powerUp->GetImageHandle());
    powerUp->KillMe(); // Remove the power-up from the game
}

void Player::SetName(const std::string& playerName) {
    name = playerName;
}

void Player::UpdateScore(int points) {
    score += points;
}

void Player::UpdateLevel(int newLevel) {
    level = newLevel;
}

const std::string& Player::GetName() const {
    return name;
}

int Player::GetAttribute() const {
    return activeAttributes.empty() ? -1 : activeAttributes.front();
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

void Player::SetHealth(int health) {
    this->health = health;
}

void Player::AddAttribute(int attribute) {
    acquiredAttributes.push_back(attribute);
}

void Player::SetActiveAttributes(const std::vector<int>& attributes) {
    activeAttributes = attributes;
}

const std::vector<int>& Player::GetActiveAttributes() const {
    return activeAttributes;
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        Death();
    }
}

void Player::Attack(Enemy& enemy) {
    int baseDamage = attackPower;
    int finalDamage = baseDamage;

    for (int attr : activeAttributes) {
        if (attr == ATTR_FIRE && enemy.GetAttribute() == ATTR_WATER) {
            finalDamage /= 2;
        }
        else if (attr == ATTR_WATER && enemy.GetAttribute() == ATTR_FIRE) {
            finalDamage *= 2;
        }
        // Other attribute interactions...
    }

    if (finalDamage > 0) {
        enemy.TakeDamage(finalDamage);
    }
}

void Player::Death() {
    SetAnimationState(Death_);
}
