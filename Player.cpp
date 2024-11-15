#include "Player.h"
#include "PowerUp.h"
#include "Engine/Image.h"


Player::Player(GameObject* parent)
    : GameObject(parent,"Player"),
    name(""),
    Attribute(-1),
    health(100), 
    score(0), 
    level(1),
    activePowerUp(-1),
    animation(nullptr) ,
    currentState(Idle_)

{
 IdleImg=-1;
     RunImg = -1;
     JumpImg = -1;
     FallImg = -1;
     HitImg = -1;
     AttackImg = -1;
     DashImg = -1;
     DeathImg = -1;
}

Player::~Player() {
    delete animation;
}

void Player::Initialize()
{
 //testing a animation first
    IdleImg = Image::Load("Player/Idle.png");
    animation=new Animation(48, 48, 12, 0.055f, IdleImg);

   
}

void Player::Update() {
    animation->Update();
}

void Player::Draw() {
    animation->Draw(50.0f,500.0f);
}

void Player::Release() {
    // 開放コード
}

void Player::Attack() {
    currentState = Attack_;
}

void Player::Hit(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    currentState = Hit_;
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
    return Attribute;
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

void Player::SetAttribute(int handle)
{
    this->Attribute = handle;
}


void Player::SetActivePowerUp(int handle)
{
    this->activePowerUp = handle;

}

void Player::Run()
{
}

void Player::Jump()
{
}

void Player::fall()
{
}

void Player::Dash()
{
}

void Player::Death()
{
}
