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
    Player(GameObject* parent, const std::string& name, int attributeImageHandle);

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

    // 攻撃
    void Attack();

    // ダメージを受ける
    void TakeDamage(int amount);

    // パワーアップを適用
    void ApplyPowerUp(int powerUpImageHandle);

    // パワーアップを収集
    void CollectPowerUp(PowerUp* powerUp);

    // プレイヤー名を設定
    void SetName(const std::string& playerName);

    // スコアを更新
    void UpdateScore(int points);

    // レベルを更新
    void UpdateLevel(int newLevel);

    // ゲッター
    const std::string& GetName() const;
    int GetAttributeImageHandle() const;
    int GetHealth() const;
    int GetScore() const;
    int GetLevel() const;

private:
    int Shadow_img;
    std::string name;
    int attributeImageHandle;
    int health;
    int score;
    int level;
    int activePowerUpImageHandle;
    AnimationManager animationManager;
    Animation* currentAnimation;
};
