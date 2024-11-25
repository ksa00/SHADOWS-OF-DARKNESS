#pragma once
#include "Attributes.h"

class DarkAttribute : public Attribute {
public:
    DarkAttribute();
    ~DarkAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
