#include "WindAttribute.h"
#include "Engine/Image.h"
#include "Animation.h"

WindAttribute::WindAttribute() : Attribute(WIND) {
    LoadImage();
}

WindAttribute::~WindAttribute() {
    Image::Release(imageHandle_);
}

void WindAttribute::LoadImage() {
    imageHandle_ = Image::Load("path_to_wind_image.png");
}

int WindAttribute::GetImageHandle() const {
    return imageHandle_;
}

void WindAttribute::SetAttackAnimation(Animation* animation) const {
    animation->SetAnimation(64, 64, 8, 0.05f, imageHandle_); // Example values for wind attack
}
