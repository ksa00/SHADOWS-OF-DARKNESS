#pragma once
#include "Engine/GameObject.h"

// TitleScene class
class TitleScene : public GameObject {
public:
    TitleScene(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:
    bool isAttributeSelectionNeeded_;
};
