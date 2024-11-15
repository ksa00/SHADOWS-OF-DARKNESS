#include "PowerUp.h"

PowerUp::PowerUp(GameObject* parent)
    : GameObject(parent),PowerImg(-1) {}

void PowerUp::Initialize() {
    // 初期化コード
}

void PowerUp::Update() {
    // 更新コード
}

void PowerUp::Draw() {
    // 描画コード
}

void PowerUp::Release() {
    // 開放コード
}

int PowerUp::GetImageHandle() const
{
    return PowerImg;
}

