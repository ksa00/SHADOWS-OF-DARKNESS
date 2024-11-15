#pragma once
#include <string>
#include <vector>
#include "Engine/Image.h" // Include your Image namespace
#include<unordered_map>

class Animation
{
public:
    Animation(const std::string& name, int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle);

    void Update();
    void Draw(int x, int y);

private:
    std::string name;
    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration;
    float currentTime;
    int currentFrame;
    int imageHandle;
};

class AnimationManager
{
public:
    void AddAnimation(const std::string& name, Animation* animation);
    Animation* GetAnimation(const std::string& name);

private:
    std::unordered_map<std::string, Animation*> animations;
};
