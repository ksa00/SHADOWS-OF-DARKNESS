#pragma once
#include "Attributes.h"

class IceAttribute : public Attribute {
public:
    IceAttribute();
    ~IceAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
