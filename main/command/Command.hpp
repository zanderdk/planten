#ifndef COMMAND_H
#define COMMAND_H

#include <cJSON.h>
#include "../led/rgb.hpp"
#include <string>

class Command {
    public:
        virtual std::string type() = 0;
        Command(Command &c) {}
        Command() {}
};

class SolidCommand: public Command {
    public:
        rgb color;
        SolidCommand(rgb color): color(color) {}
        SolidCommand(SolidCommand &s): Command(s), color(s.color) {}
        virtual std::string type() override;
};

#endif