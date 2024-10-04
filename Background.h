#pragma once
#include "Engine/GameObject.h"
#include"vector"
struct ParallaxLayer {
    int* hBackGround;
    float scrollSpeed; // Speed at which the layer scrolls
    float position; // Current position of the layer
};
class Background : public GameObject
{
    std::vector<ParallaxLayer>layers;
    int screenWidth;




public:
    Background(GameObject* parent);

    ~Background();

    void Initialize() override;
   
    void Update() override;

    void Draw() override;

    void Release() override;
    void AddLayer(int* hImg, float scrollspeed);
};

