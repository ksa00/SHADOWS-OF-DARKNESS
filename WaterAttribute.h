#pragma once
#include "Attributes.h"

class WaterAttribute : public Attribute {
public:
    WaterAttribute();
    ~WaterAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
