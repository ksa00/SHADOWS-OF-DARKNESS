#pragma once
#include <string>
#include <vector>
#include "Engine/Image.h" // Include your Image namespace

class Animation
{
public:
    Animation( int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle);
    void Update();
    void Draw(float x, float y);
    void SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle);

private:
 
    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration;
    float currentTime;
    int currentFrame;
    int imageHandle;
};

