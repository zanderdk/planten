#ifndef EFFECTHANDLER_T
#define EFFECTHANDLER_T

#include <stdint.h>
#include <memory>
#include "IRGB.hpp"
#include "Effect.hpp"

extern const char *EFFECT_HANDLER_TAG;

class EffectHandler {
    public:
        void setEffect(std::shared_ptr<Effect> e);
        void update(uint32_t time);
        void setColor(rgb color);
        int updateTime;
        EffectHandler(int u): updateTime(u) {}

    private:
        std::shared_ptr<Effect> _currentEffect;
};

#endif