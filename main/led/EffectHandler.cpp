#include "EffectHandler.hpp"
#include "esp_log.h"
#include "led.hpp"
#include "SolidEffect.hpp"

const char *EFFECT_HANDLER_TAG = "EFFECT_HANDLER";

void EffectHandler::setEffect(std::shared_ptr<Effect> e) {
    _currentEffect = e;
    ESP_LOGI(EFFECT_HANDLER_TAG, "setting effect to %s", e->name().c_str());
    _currentEffect->setup();
}

void EffectHandler::update(uint32_t time) {
    if(_currentEffect) {
        _currentEffect->update(time);
    }
}