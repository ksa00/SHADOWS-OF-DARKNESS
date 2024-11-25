#include "AttributeFactory.h"

Attribute* AttributeFactory::CreateAttribute(Attribute::Type type) {
    switch (type) {
    case Attribute::FIRE:
        return new FireAttribute();
    case Attribute::WATER:
        return new WaterAttribute();
    case Attribute::WIND:
        return new WindAttribute();
    case Attribute::EARTH:
        return new EarthAttribute();
    case Attribute::ELECTRIC:
        return new ElectricAttribute();
    case Attribute::ICE:
        return new IceAttribute();
    case Attribute::DARK:
        return new DarkAttribute();
    default:
        return nullptr;
    }
}
