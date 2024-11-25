#pragma once
#include "Attributes.h"
#include "FireAttribute.h"
#include "WaterAttribute.h"
#include "WindAttribute.h"
#include "EarthAttribute.h"
#include "ElectricAttribute.h"
#include "IceAttribute.h"
#include "DarkAttribute.h"

class AttributeFactory {
public:
    static Attribute* CreateAttribute(Attribute::Type type);
};
