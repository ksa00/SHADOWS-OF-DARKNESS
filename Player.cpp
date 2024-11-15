#include "Player.h"
#include "PowerUp.h"
#include "Engine/Image.h"


Player::Player(GameObject* parent, const std::string& name, int attributeImageHandle)
    : GameObject(parent, name), name(name), attributeImageHandle(attributeImageHandle), health(100), currentAnimation(nullptr) {}

Player::~Player() {}

void Player::Initialize() {
    // Load the spritesheet
    int spritesheetHandle = Image::Load("spritesheet.png");

    // Initialize animations with frames from the spritesheet
    animationManager.AddAnimation("Idle", new Animation("Idle", 48, 48, 4, 0.25f, spritesheetHandle));
    animationManager.AddAnimation("Run", new Animation("Run", 48, 48, 6, 0.1f, spritesheetHandle));
    animationManager.AddAnimation("Jump", new Animation("Jump", 48, 48, 2, 0.2f, spritesheetHandle));
    animationManager.AddAnimation("Fall", new Animation("Fall", 48, 48, 2, 0.2f, spritesheetHandle));
    animationManager.AddAnimation("Hit", new Animation("Hit", 48, 48, 3, 0.15f, spritesheetHandle));
    animationManager.AddAnimation("Attack", new Animation("Attack", 131, 56, 5, 0.1f, spritesheetHandle));
    animationManager.AddAnimation("Dash", new Animation("Dash", 112, 56, 4, 0.1f, spritesheetHandle));
    animationManager.AddAnimation("Death", new Animation("Death", 76, 48, 6, 0.2f, spritesheetHandle));

    currentAnimation = animationManager.GetAnimation("Idle");
}

void Player::Update() {
    // Update the current animation
    if (currentAnimation) {
        currentAnimation->Update();
    }
}

void Player::Draw() {
    // Draw the current animation
    if (currentAnimation) {
        currentAnimation->Draw(100, 100); // Example position
    }
}

void Player::Release() {
    // 開放コード
}

void Player::Attack() {
    currentAnimation = animationManager.GetAnimation("Attack");
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    currentAnimation = animationManager.GetAnimation("Hit");
}

void Player::ApplyPowerUp(int powerUpImageHandle) {
    activePowerUpImageHandle = powerUpImageHandle;
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

int Player::GetAttributeImageHandle() const {
    return attributeImageHandle;
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
