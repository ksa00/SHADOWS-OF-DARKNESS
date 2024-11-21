#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

class Stage : public GameObject {
public:
    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;


private:
    int tilesetImage_; // Handle for the tileset image

};
