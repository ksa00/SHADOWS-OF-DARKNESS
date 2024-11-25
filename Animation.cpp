#include "Animation.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

Animation::Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle, int startFrame, bool loop_)
    : frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentTime(0), currentFrame(startFrame), startFrame(startFrame), imageHandle(imageHandle), loop(loop_) {
    CalculateFrames();
}

void Animation::Update() {
    currentTime += 1.0f / 60.0f; // Assuming a 60 FPS update rate
    if (currentTime >= frameDuration) {
        currentTime -= frameDuration;
        if (loop) {
            currentFrame = (currentFrame + 1) % frameCount + startFrame;
        }
        else {
            if (currentFrame < startFrame + frameCount - 1) {
                currentFrame++;
            }
        }
    }

    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Animation::Draw(const Transform& transform, bool facingRight) {
    if (imageHandle < 0) {
        return;
    }

    int frameX = frames[currentFrame].left;
    int frameY = frames[currentFrame].top;

    Transform ndcTransform = transform;
    Image::ConvertToNDC(transform, ndcTransform.position_.x, ndcTransform.position_.y);

    if (facingRight) {
        Image::SetRect(imageHandle, frameX, frameY, frameWidth, frameHeight);
    }
    else {
        Image::SetRect(imageHandle, frameX + frameWidth, frameY, -frameWidth, frameHeight);
        ndcTransform.scale_.x = -1.0f;
    }

    Image::SetTransform(imageHandle, ndcTransform);
    Image::Draw(imageHandle);

    for (auto anim : overlayAnimations) {
        anim->Draw(ndcTransform, facingRight);
    }
}

void Animation::SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle, int startFrame, bool loop_) {
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->frameDuration = frameDuration;
    this->imageHandle = imageHandle;
    this->startFrame = startFrame;
    this->loop = loop_;
    currentFrame = startFrame;
    currentTime = 0;
    CalculateFrames();
}

void Animation::AddOverlayAnimation(Animation* animation) {
    overlayAnimations.push_back(animation);
}

void Animation::ClearOverlayAnimations() {
    overlayAnimations.clear();
}

void Animation::CalculateFrames() {
    frames.clear();
    int imageWidth = Image::GetWidth(imageHandle);
    int imageHeight = Image::GetHeight(imageHandle);
    for (int i = startFrame; i < startFrame + frameCount; ++i) {
        int x = (i % (imageWidth / frameWidth)) * frameWidth;
        int y = (i / (imageWidth / frameWidth)) * frameHeight;
        frames.push_back({ x, y, x + frameWidth, y + frameHeight });
    }
}
bool Animation::IsAnimationComplete() const {
    return !loop && currentFrame == startFrame + frameCount - 1;
}
