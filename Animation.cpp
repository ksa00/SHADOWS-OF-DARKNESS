#include "Animation.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Debug.h" // For debug logging

Animation::Animation(int frameCount, float frameDuration, int imageHandle, int startFrame, bool loop)
    : frameCount(frameCount), frameDuration(frameDuration), currentTime(0), currentFrame(startFrame), startFrame(startFrame), imageHandle(imageHandle), loop(loop) {
    CalculateFrames();
}

void Animation::Update() {
    currentTime += 1.0f / 60.0f; // Assuming a 60 FPS update rate

    Debug::Log("Before Update - Current Frame: " + std::to_string(currentFrame) + " | Current Time: " + std::to_string(currentTime) + " | Frame Duration: " + std::to_string(frameDuration));

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

        Debug::Log("After Frame Update - Current Frame: " + std::to_string(currentFrame) + " | Current Time: " + std::to_string(currentTime));
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

void Animation::SetAnimation(int frameCount, float frameDuration, int imageHandle, int startFrame, bool loop) {
    this->frameCount = frameCount;
    this->frameDuration = frameDuration;
    this->imageHandle = imageHandle;
    this->startFrame = startFrame;
    this->loop = loop;
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
    frameWidth = imageWidth / frameCount; // Automatically calculate frame width
    frameHeight = imageHeight; // Assuming a single row of frames

    for (int i = startFrame; i < startFrame + frameCount; ++i) {
        int x = i * frameWidth;
        int y = 0;
        frames.push_back({ x, y, x + frameWidth, y + frameHeight });
    }
}

bool Animation::IsAnimationComplete() const {
    return !loop && currentFrame == startFrame + frameCount - 1;
}
