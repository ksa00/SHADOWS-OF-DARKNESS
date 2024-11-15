#include "Animation.h"
Animation::Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle)
    :frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentTime(0), currentFrame(0), imageHandle(imageHandle) {}

void Animation::Update() {
    currentTime += 1.0f / 60.0f; // Assuming a 60 FPS update rate
    if (currentTime >= frameDuration) {
        currentTime -= frameDuration;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Animation::Draw(float x, float y) {
    int frameX = (currentFrame % (Image::GetWidth(imageHandle) / frameWidth)) * frameWidth;
    int frameY = (currentFrame / (Image::GetWidth(imageHandle) / frameWidth)) * frameHeight;
    Image::SetRect(imageHandle, frameX, frameY, frameWidth, frameHeight);
    // Set the transform for the position
    float screenWidth = 800.0f; // Example screen width
    float screenHeight = 600.0f; // Example screen height
    Transform trans;
   // trans.position_ = {x- screenWidth /2, y- screenHeight /2, 0.0f };
    Image::SetTransform(imageHandle, trans);
    Image::Draw(imageHandle);
}

void Animation::SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle) {
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->frameDuration = frameDuration;
    this->imageHandle = imageHandle;
    currentFrame = 0;
    currentTime = 0;
}