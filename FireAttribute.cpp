#include "FireAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

FireAttribute::FireAttribute() : Attribute(FIRE) {
    LoadImage();
}

FireAttribute::~FireAttribute() {
    Image::Release(imageHandle_);
}

void FireAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_fire_image.png");
}

int FireAttribute::GetImageHandle() const {
    return imageHandle_;
}

void FireAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for fire attack
}
