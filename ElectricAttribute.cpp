#include "ElectricAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

ElectricAttribute::ElectricAttribute() : Attribute(ELECTRIC) {
    LoadImage();
}

ElectricAttribute::~ElectricAttribute() {
    Image::Release(imageHandle_);
}

void ElectricAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_electric_image.png");
}

int ElectricAttribute::GetImageHandle() const {
    return imageHandle_;
}

void ElectricAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for electric attack
}
