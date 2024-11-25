#pragma once
#include "Engine/Image.h"
#include"Animation.h"

class Attribute {
public:
    enum Type {
        FIRE,
        WATER,
        WIND,
        EARTH,
        ELECTRIC,
        ICE,
        DARK
        // Add other attributes as needed
    };

    explicit Attribute(Type type);
    virtual ~Attribute();

    Type GetType() const;
    virtual int GetImageHandle() const;
    virtual void SetAttackAnimation(Animation* animation) const = 0;

protected:
    Type type_;
    int imageHandle_;

    virtual void LoadImage() = 0;
};
