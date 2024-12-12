#include "Animation.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Debug.h"

Animation::Animation(int totalFrameCount, float frameDuration, int imageHandle, int startFrame, int subsetFrameCount, bool loop)
    : totalFrameCount(totalFrameCount),
    frameDuration(frameDuration),
    currentTime(0),
    currentFrame(startFrame),
    startFrame(startFrame),
    imageHandle(imageHandle),
    loop(loop),
    frameHeight(0),
    frameWidth(0) {
    // Ensure subsetFrameCount is valid
    if (subsetFrameCount == -1 || subsetFrameCount <= 0) {
        this->subsetFrameCount = totalFrameCount - startFrame; // Default to the remaining frames
    }
    else {
        this->subsetFrameCount = subsetFrameCount;
    }
    CalculateFrames();
}

void Animation::Update() {
    currentTime += 1.0f / 60.0f; // Assuming a 60 FPS update rate

    Debug::Log("Before Update - Current Frame: " + std::to_string(currentFrame) + " | Current Time: " + std::to_string(currentTime) + " | Frame Duration: " + std::to_string(frameDuration) + "\n");

    if (currentTime >= frameDuration) {
        currentTime -= frameDuration;

        if (loop) {
            if (subsetFrameCount > 0) {
                currentFrame = startFrame + (currentFrame + 1 - startFrame) % subsetFrameCount;
            }
        }
        else {
            if (currentFrame < startFrame + subsetFrameCount - 1) {
                currentFrame++;
            }
            else {
                Debug::Log("Non-looping animation reached the end: " + std::to_string(currentFrame) + "\n");
            }
        }

        Debug::Log("After Frame Update - Current Frame: " + std::to_string(currentFrame) + " | Current Time: " + std::to_string(currentTime) + "\n");
    }

    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Animation::Draw(const Transform& transform, bool facingRight) {
    if (imageHandle < 0) {
        return;
    }

    int frameIndex = currentFrame - startFrame;
    if (frameIndex < 0 || frameIndex >= static_cast<int>(frames.size())) {
return;
    }

    int frameX = frames[frameIndex].left;
    int frameY = frames[frameIndex].top;

    Transform ndcTransform = transform;
    Image::ConvertToNDC(transform, ndcTransform.position_.x, ndcTransform.position_.y);

    Debug::Log("Drawing Frame - Current Frame: " + std::to_string(currentFrame) + " | Position: (" + std::to_string(ndcTransform.position_.x) + ", " + std::to_string(ndcTransform.position_.y) + ") | Facing Right: " + std::to_string(facingRight) + "\n");

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

void Animation::SetAnimation(int totalFrameCount, float frameDuration, int imageHandle, int startFrame, int subsetFrameCount, bool loop) {
    this->totalFrameCount = totalFrameCount;
    this->frameDuration = frameDuration;
    this->imageHandle = imageHandle;
    this->startFrame = startFrame;
    this->loop = loop;
    // Ensure subsetFrameCount is valid
    this->subsetFrameCount = (subsetFrameCount == -1 || subsetFrameCount <= 0) ? totalFrameCount - startFrame : subsetFrameCount;
    currentFrame = startFrame;
    currentTime = 0;
    CalculateFrames();
    Debug::Log("SetAnimation - Total Frame Count: " + std::to_string(totalFrameCount) + " | Frame Duration: " + std::to_string(frameDuration) + " | Start Frame: " + std::to_string(startFrame) + " | Subset Frame Count: " + std::to_string(this->subsetFrameCount) + " | Loop: " + std::to_string(loop) + "\n");
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
    frameWidth = imageWidth / totalFrameCount; // Automatically calculate frame width
    frameHeight = imageHeight; // Assuming a single row of frames

    for (int i = startFrame; i < startFrame + subsetFrameCount; ++i) {
        int x = i * frameWidth;
        int y = 0;
        frames.push_back({ x, y, x + frameWidth, y + frameHeight });
    }
    Debug::Log("CalculateFrames - Frame Width: " + std::to_string(frameWidth) + " | Frame Height: " + std::to_string(frameHeight) + "\n");
}

bool Animation::IsAnimationComplete() const {
    return(!loop && currentFrame == startFrame + subsetFrameCount - 1);
}

