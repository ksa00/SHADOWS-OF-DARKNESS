#pragma once
#include "Attributes.h"

class WindAttribute : public Attribute {
public:
    WindAttribute();
    ~WindAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
