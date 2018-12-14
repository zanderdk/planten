#ifndef LED_H
#define LED_H

#include "PWM.h"
#include <array>
#include "IRGB.hpp"

#define RED_GPIO (CONFIG_RED_GPIO)
#define GREEN_GPIO (CONFIG_GREEN_GPIO)
#define BLUE_GPIO (CONFIG_BLUE_GPIO)

#define NUM_CHANNELS (3)
#define LED_MAX_VAL (8192)

extern const char *LED_TAG;

class RGBLed: public IRGB {
    public:
        RGBLed(int redGpio = RED_GPIO, 
               int greenGpio = GREEN_GPIO, 
               int blueGpio = BLUE_GPIO);
        ~RGBLed();
    
        std::array<PWM *, NUM_CHANNELS> pwmChannels();
        std::array<ledc_channel_t, NUM_CHANNELS> channels();

        void setPercentRed(double percent) override;
        void setPercentGreen(double percent) override;
        void setPercentBlue(double percent) override;
        void fadeToPercentRed(double percent, int fadeTime = 1000) override;
        void fadeToPercentGreen(double percent, int fadeTime = 1000) override;
        void fadeToPercentBlue(double percent, int fadeTime = 1000) override;
    
        void setPercentIndex(int index, double percent);
        void fadeToPercentIndex(int index, double percent, int fadeTime = 1000);

    private:
        PWM redPWM;
        PWM greenPWM;
        PWM bluePWM;

        std::array<PWM *, NUM_CHANNELS> _pwmChannels;
        std::array<ledc_channel_t, NUM_CHANNELS> _channels;
};

#endif // LED_H