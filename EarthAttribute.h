#pragma once
#include "Attributes.h"

class EarthAttribute : public Attribute {
public:
    EarthAttribute();
    ~EarthAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
