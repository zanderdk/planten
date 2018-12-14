#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "Effect.hpp"
#include <stdint.h>
#include "rgb.hpp"

class FadeEffect: public Effect {
    public:
        void setup() override;
        void update(uint32_t time) override;
        std::string name() override {
            return "Fade";
        }

        FadeEffect(FadeEffect &e): Effect(e) {
            _current = e._current;
            _fadeTime = e._fadeTime;
            _lastUpdateTime = e._lastUpdateTime;
            _holdTime = e._holdTime;
        }

        FadeEffect(std::shared_ptr<IRGB> led, int updateTime, int fadeTime = 5000, int holdTime = 5000):
            Effect(led, updateTime) {
                _current = 0;
                _lastUpdateTime = 0;
                _fadeTime = fadeTime;
                _holdTime = holdTime;
            }
    
    protected:
        int _current;
        int _fadeTime;
        int _lastUpdateTime;
        int _holdTime;
};

#endif