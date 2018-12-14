#ifndef IRGB_H
#define IRGB_H

#include "rgb.hpp"
#include "esp_log.h"
#include "IRGBSub.hpp"
#include <vector>

extern const char *IRGB_TAG;

class IRGB {
    public:
        virtual void setPercentRed(double percent);
        virtual void setPercentGreen(double percent);
        virtual void setPercentBlue(double percent);

        virtual void fadeToPercentRed(double percent, int fadeTime);
        virtual void fadeToPercentGreen(double percent, int fadeTime);
        virtual void fadeToPercentBlue(double percent, int fadeTime);

        void setPercentRGB(rgb percent);
        void fadeToPercentRGB(rgb percent, int fadeTime);
};

#endif // IRGB_H