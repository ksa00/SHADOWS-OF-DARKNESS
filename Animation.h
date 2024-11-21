#pragma once
#include <vector>
#include "Engine/Image.h"

class Animation {
public:
    Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle);
    void Update();
    void Draw(const Transform& transform, bool facingRight = false);
    void SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle);
    void AddOverlayAnimation(Animation* animation);
    void ClearOverlayAnimations();

private:
    struct Frame {
        int x, y, width, height;
    };

    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration; // Duration of each frame in seconds
    float currentTime;   // Time accumulator
    int currentFrame;
    int imageHandle;

    std::vector<Frame> frames;
    std::vector<Animation*> overlayAnimations;

    void CalculateFrames();
    void ConvertToNDC(const Transform& transform, float& ndcX, float& ndcY);
};
