#include "Animation.h"

Animation::Animation(const std::string& name, int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle)
    : name(name), frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentTime(0), currentFrame(0), imageHandle(imageHandle) {}

void Animation::Update() {
    currentTime += frameDuration;
    if (currentTime >= frameDuration) {
        currentTime = 0;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Animation::Draw(int x, int y) {
    int frameX = (currentFrame % (Image::GetWidth(imageHandle) / frameWidth)) * frameWidth;
    int frameY = (currentFrame / (Image::GetWidth(imageHandle) / frameWidth)) * frameHeight;
    Image::SetRect(imageHandle, frameX, frameY, frameWidth, frameHeight);
    Image::Draw(imageHandle);
}

void AnimationManager::AddAnimation(const std::string& name, Animation* animation) {
    animations[name] = animation;
}

Animation* AnimationManager::GetAnimation(const std::string& name) {
    return animations[name];
}
