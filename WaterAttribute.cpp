#include "WaterAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

WaterAttribute::WaterAttribute() : Attribute(WATER) {
    LoadImage();
}

WaterAttribute::~WaterAttribute() {
    Image::Release(imageHandle_);
}

void WaterAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_water_image.png");
}

int WaterAttribute::GetImageHandle() const {
    return imageHandle_;
}

void WaterAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for water attack
}
