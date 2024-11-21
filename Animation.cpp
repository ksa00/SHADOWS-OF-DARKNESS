#include "Animation.h"
#include "Engine/Direct3D.h" // Corrected include path for Direct3D

Animation::Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle)
    : frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentTime(0), currentFrame(0), imageHandle(imageHandle) {
    CalculateFrames();
}

void Animation::Update() {
    currentTime += 1.0f / 60.0f; // Assuming a 60 FPS update rate
    if (currentTime >= frameDuration) {
        currentTime -= frameDuration;
        currentFrame = (currentFrame + 1) % frameCount;
    }

    for (auto anim : overlayAnimations) {
        anim->Update();
    }
}

void Animation::Draw(const Transform& transform, bool facingRight) {
    if (imageHandle < 0) {
        return;
    }

    // Convert world coordinates to NDC
    float ndcX, ndcY;
    ConvertToNDC(transform, ndcX, ndcY);

    int frameX = frames[currentFrame].x;
    int frameY = frames[currentFrame].y;

    Transform ndcTransform = transform;
    ndcTransform.position_ = { ndcX, ndcY, transform.position_.z };
    // Set the frame rectangle for the current frame
    if (facingRight) {
        Image::SetRect(imageHandle, frameX, frameY, frameWidth, frameHeight);
    }
    else {
        // Adjust for the horizontal flip
        Image::SetRect(imageHandle, frameX + frameWidth, frameY, -frameWidth, frameHeight);
        ndcTransform.scale_.x = -1.0f;
    }


    Image::SetTransform(imageHandle, ndcTransform);
    Image::Draw(imageHandle);

    // Ensure overlay animations are drawn with the correct transform and facing direction
    for (auto anim : overlayAnimations) {
        anim->Draw(ndcTransform, facingRight);
    }
}

void Animation::SetAnimation(int frameWidth, int frameHeight, int frameCount, float frameDuration, int imageHandle) {
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->frameDuration = frameDuration;
    this->imageHandle = imageHandle;
    currentFrame = 0;
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
    for (int i = 0; i < frameCount; ++i) {
        int x = (i % (imageWidth / frameWidth)) * frameWidth;
        int y = (i / (imageWidth / frameWidth)) * frameHeight;
        frames.push_back({ x, y, frameWidth, frameHeight });
    }
}

void Animation::ConvertToNDC(const Transform& transform, float& ndcX, float& ndcY) {
    ndcX = (2.0f * transform.position_.x) / Direct3D::screenWidth_ - 1.0f;
    ndcY = 1.0f - (2.0f * transform.position_.y) / Direct3D::screenHeight_;
}
