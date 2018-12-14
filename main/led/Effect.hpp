#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>
#include <memory>
#include "IRGB.hpp"

class Effect {
    public:
        virtual void setup() = 0;
        virtual void update(uint32_t time) = 0;
        virtual std::string name() = 0;

        Effect(Effect &e): _led(e._led), _updateTime(e._updateTime) {}
        Effect(std::shared_ptr<IRGB> led, int _updateTime): _led(led), _updateTime(_updateTime) {}

    protected:
        std::shared_ptr<IRGB> _led;
        int _updateTime;
};

#endif