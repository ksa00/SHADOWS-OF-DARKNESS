#pragma once
#include "Attributes.h"

class ElectricAttribute : public Attribute {
public:
    ElectricAttribute();
    ~ElectricAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
