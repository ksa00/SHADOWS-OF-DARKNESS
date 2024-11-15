#pragma once
#include "Engine/GameObject.h"

class PowerUp : public GameObject
{
public:
    PowerUp(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    int GetImageHandle() const;

private:
    int PowerImg;
};
