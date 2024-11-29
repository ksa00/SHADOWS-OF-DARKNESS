#pragma once
#include <vector>
#include "Engine/Image.h"

class Animation {
public:
    Animation(int totalFrameCount, float frameDuration, int imageHandle, int startFrame = 0, int subsetFrameCount = -1, bool loop = true);

    void Update();
    void Draw(const Transform& transform, bool facingRight);
    void SetAnimation(int totalFrameCount, float frameDuration, int imageHandle, int startFrame = 0, int subsetFrameCount = -1, bool loop = true);
    void AddOverlayAnimation(Animation* animation);
    void ClearOverlayAnimations();
    bool IsAnimationComplete() const;

private:
    void CalculateFrames();

    int totalFrameCount;
    int subsetFrameCount; // Number of frames in the subset to animate
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
