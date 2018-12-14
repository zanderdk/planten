#ifndef IRGBSUB_H
#define IRGBSUB_H

#include "./rgb.hpp"

class IRGBSub {
    public:
        virtual void update(rgb color) = 0;
};

#endif // IRGBSUB_H