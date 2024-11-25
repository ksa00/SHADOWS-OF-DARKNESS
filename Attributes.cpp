#include "Attributes.h"
#include "Engine/Image.h"

Attribute::Attribute(Type type) : type_(type), imageHandle_(-1) {
}

Attribute::~Attribute() {
    Image::Release(imageHandle_);
}

Attribute::Type Attribute::GetType() const {
    return type_;
}

int Attribute::GetImageHandle() const {
    return imageHandle_;
}
