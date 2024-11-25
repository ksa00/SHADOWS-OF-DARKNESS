#pragma once
#include "Attributes.h"

class FireAttribute : public Attribute {
public:
    FireAttribute();
    ~FireAttribute();

    int GetImageHandle() const override;
    void SetAttackAnimation(Animation* animation) const override;

protected:
    void LoadImage() override;
};
