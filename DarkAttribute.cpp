#include "DarkAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

DarkAttribute::DarkAttribute() : Attribute(DARK) {
    LoadImage();
}

DarkAttribute::~DarkAttribute() {
    Image::Release(imageHandle_);
}

void DarkAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_dark_image.png");
}

int DarkAttribute::GetImageHandle() const {
    return imageHandle_;
}

void DarkAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for dark attack
}
