#include "FadeEffect.hpp"

const rgb OFF = { 0, 0, 0 };
const rgb RED = { 255, 0, 0 };
const rgb GREEN = { 0, 255, 0 };
const rgb BLUE = { 0, 0, 255 };
const rgb ORANGE = { 255, 165, 0 };
const rgb YELLOW = { 255, 255, 0 };
const rgb PURPLE = { 148, 0, 211 };
const rgb INDIGO = { 75, 0, 130 };
const rgb VIOLET = { 238, 130, 238 };
const rgb WHITE = { 255, 255, 255 };

const rgb Colors[10] = {
    OFF,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    YELLOW,
    PURPLE,
    INDIGO,
    VIOLET,
    WHITE
};

void FadeEffect::setup() {
    _led->setPercentRGB(Colors[_current]);
}

void FadeEffect::update(uint32_t time) {
    if (time >= (_lastUpdateTime + _fadeTime + _holdTime)) {
        _current = (_current + 1) % 11;
        _led->fadeToPercentRGB(Colors[_current], _fadeTime);
        _lastUpdateTime = time;
    }
}