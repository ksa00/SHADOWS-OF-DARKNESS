#pragma once
#include"Engine/Image.h"
#include <vector>
class Animation {
public:
    Animation(int frameCount, float frameDuration, int imageHandle, int startFrame = 0, bool loop = true);
    void Update();
    void Draw(const Transform& transform, bool facingRight);
    void SetAnimation(int frameCount, float frameDuration, int imageHandle, int startFrame = 0, bool loop = true);
    void AddOverlayAnimation(Animation* animation);
    void ClearOverlayAnimations();
    bool IsAnimationComplete() const;

private:
    void CalculateFrames();
    int frameCount;
    float frameDuration;
    float currentTime;
    int currentFrame;
    int startFrame;
    int imageHandle;
    bool loop;
    int frameWidth;
    int frameHeight;
    std::vector<RECT> frames;
    std::vector<Animation*> overlayAnimations;
};
