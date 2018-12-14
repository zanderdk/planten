#include "SolidEffect.hpp"

void SolidEffect::setup() {
    _led->setPercentRGB(_color);
}

void SolidEffect::update(uint32_t time) {
    _led->setPercentRGB(_color);
}