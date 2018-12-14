#ifndef SOLIDEFFECT_H
#define SOLIDEFFECT_H

#include "Effect.hpp"
#include <stdint.h>
#include "rgb.hpp"
#include <string>
#include "../utils.cpp"

class SolidEffect: public Effect {
    public:
        void setup() override;
        void update(uint32_t time) override;

        std::string name() override {
            std::string str = "solid color (";
            str += to_string(_color.r);
            str += ", ";
            str += to_string(_color.g);
            str += ", ";
            str += to_string(_color.b);
            str += ")";
            return str;
        }

        SolidEffect(SolidEffect &e): Effect(e), _color(e._color) {}
        SolidEffect(std::shared_ptr<IRGB> led, int updateTime, rgb c):
            Effect(led, updateTime),_color(c) {}
    
    protected:
        rgb _color;
};

#endif