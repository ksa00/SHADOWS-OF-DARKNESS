#include "EarthAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

EarthAttribute::EarthAttribute() : Attribute(EARTH) {
    LoadImage();
}

EarthAttribute::~EarthAttribute() {
    Image::Release(imageHandle_);
}

void EarthAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_earth_image.png");
}

int EarthAttribute::GetImageHandle() const {
    return imageHandle_;
}

void EarthAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for earth attack
}
