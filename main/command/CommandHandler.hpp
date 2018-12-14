#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "../led/EffectHandler.hpp"
#include "Command.hpp"

extern const char *COMMAND_HANDLER_TAG;

class CommandHandler {
    public:
        CommandHandler(EffectHandler *h, std::shared_ptr<IRGB> led): _effectHandler(h), _led(led) {}
        void handleCommand(std::string s);
        static std::shared_ptr<Command> makeCommand(std::string cmdStr);
        std::shared_ptr<IRGB> getLed();

    private:
        EffectHandler *_effectHandler;
        std::shared_ptr<IRGB> _led;
};

#endif