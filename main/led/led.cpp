#include "led.hpp"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "driver/ledc.h"

const char *LED_TAG = "LED_task";

RGBLed::RGBLed(int redGpio, int greenGpio, int blueGpio): 
               redPWM(redGpio, 5000, LEDC_TIMER_13_BIT, LEDC_TIMER_0, LEDC_CHANNEL_0), 
               greenPWM(greenGpio, 5000, LEDC_TIMER_13_BIT, LEDC_TIMER_0, LEDC_CHANNEL_1), 
               bluePWM(blueGpio, 5000, LEDC_TIMER_13_BIT, LEDC_TIMER_0, LEDC_CHANNEL_2) {
                    ESP_LOGI(LED_TAG, "start init led");

                    _channels[0] = LEDC_CHANNEL_0;
                    _channels[1] = LEDC_CHANNEL_1;
                    _channels[2] = LEDC_CHANNEL_2;
                    _pwmChannels[0] = &redPWM;
                    _pwmChannels[1] = &greenPWM;
                    _pwmChannels[2] = &bluePWM;

                    setPercentRed(0);
                    setPercentGreen(0);
                    setPercentBlue(0);

                    ledc_fade_func_install(0);

                    ESP_LOGI(LED_TAG, "done init led");
}

RGBLed::~RGBLed() {
    ESP_LOGI(LED_TAG, "led destructor");
    ledc_fade_func_uninstall();
}

std::array<PWM *, NUM_CHANNELS> RGBLed::pwmChannels() {
    return std::array<PWM *, NUM_CHANNELS>(_pwmChannels);
}

std::array<ledc_channel_t, NUM_CHANNELS> RGBLed::channels() {
    return std::array<ledc_channel_t, NUM_CHANNELS>(_channels);
}

void RGBLed::setPercentIndex(int index, double percent) {
	if (percent > 100.0) percent = 100.0;
	uint32_t value = (LED_MAX_VAL * percent) / 100.0;
	if (value >= LED_MAX_VAL) value = LED_MAX_VAL;

	_pwmChannels[index]->setDuty(LED_MAX_VAL - value);
}

void RGBLed::fadeToPercentIndex(int index, double percent, int fadeTime) {
	if (percent > 100.0) percent = 100.0;
	uint32_t value = (LED_MAX_VAL * percent) / 100.0;
	if (value >= LED_MAX_VAL) value = LED_MAX_VAL;

    ledc_set_fade_time_and_start(LEDC_HIGH_SPEED_MODE,
                                 _channels[index],
                                 LED_MAX_VAL - value,
                                 fadeTime,
                                 LEDC_FADE_NO_WAIT);
}

void  RGBLed::setPercentRed(double percent) {
    setPercentIndex(0, percent);
}

void  RGBLed::setPercentGreen(double percent) {
    setPercentIndex(1, percent);
}

void  RGBLed::setPercentBlue(double percent) {
    setPercentIndex(2, percent);
}

void  RGBLed::fadeToPercentRed(double percent, int fadeTime) {
    fadeToPercentIndex(0, percent, fadeTime);
}

void  RGBLed::fadeToPercentGreen(double percent, int fadeTime) {
    fadeToPercentIndex(1, percent, fadeTime);
}

void  RGBLed::fadeToPercentBlue(double percent, int fadeTime) {
    fadeToPercentIndex(2, percent, fadeTime);
}