#include "IRGB.hpp"

const char *IRGB_TAG = "IRGB";

void IRGB::setPercentRGB(rgb percent) {
    setPercentRed(percent.r);
    setPercentGreen(percent.g);
    setPercentBlue(percent.b);

}

void IRGB::fadeToPercentRGB(rgb percent, int fadeTime) {
    ESP_LOGI(IRGB_TAG, "fading to: (%lf, %lf, %lf)", percent.r, percent.g, percent.b);

    fadeToPercentRed(percent.r, fadeTime);
    fadeToPercentGreen(percent.g, fadeTime);
    fadeToPercentBlue(percent.b, fadeTime);

}