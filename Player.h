#pragma once
#include "Engine/GameObject.h"
#include"PowerUp.h"
#include <string>
#include"Animation.h"

class Player : public GameObject
{
public:
    // コンストラクタ
    // 引数：parent  親オブジェクト（SceneManager）
    Player(GameObject* parent);

    // デストラクタ
    ~Player();

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;

   

    // パワーアップを適用
    void ApplyPowerUp(int powerUpImageHandle);

    // パワーアップを収集
    void CollectPowerUp(PowerUp* powerUp);

    

    // スコアを更新
    void UpdateScore(int points);

    // レベルを更新
    void UpdateLevel(int newLevel);

    // ゲッター
    const std::string& GetName() const;
    int GetAttribute() const;
    int GetHealth() const;
    int GetScore() const;
    int GetLevel() const;

  

private:
    enum State {
        Idle_,
        Run_,
        Jump_,
        Fall_,
        Hit_,
        Attack_,
        Dash_,
        Death_,
        // Add more as needed
    };
    State currentState;
    std::string name;
    int IdleImg;
    int RunImg;
    int JumpImg;
    int FallImg;
    int HitImg;
    int AttackImg;
    int DashImg;
    int DeathImg;
    int Attribute;
    int health;
    int score;
    int level;
    int activePowerUp;
    Animation* animation;
    // プレイヤー名を設定
    void SetName(const std::string& playerName);
    void SetHealth(int health);
    void SetAttribute(int handle);
    void SetActivePowerUp(int handle);
    void Run();
    void Jump();
    void fall();
    void Attack();
    void Hit(int amount);
    void Dash();
    void Death();
};
