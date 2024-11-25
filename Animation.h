#pragma once
#include"Engine/Image.h"
#include <vector>


class Animation {
public:
    Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle, int startFrame = 0, bool loop_ = true);
    void Update();
    void Draw(const Transform& transform, bool facingRight);
    void SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle, int startFrame = 0,bool loop_=true);
    void AddOverlayAnimation(Animation* animation);
    void ClearOverlayAnimations();
bool IsAnimationComplete() const;
private:
    void CalculateFrames();

    

    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration;
    float currentTime;
    int currentFrame;
    int startFrame;
    bool loop;
    int imageHandle;
    std::vector<RECT> frames;
    std::vector<Animation*> overlayAnimations;
};
