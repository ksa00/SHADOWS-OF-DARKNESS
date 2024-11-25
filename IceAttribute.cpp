#include "IceAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

IceAttribute::IceAttribute() : Attribute(ICE) {
    LoadImage();
}

IceAttribute::~IceAttribute() {
    Image::Release(imageHandle_);
}

void IceAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_ice_image.png");
}

int IceAttribute::GetImageHandle() const {
    return imageHandle_;
}

void IceAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for ice attack
}
