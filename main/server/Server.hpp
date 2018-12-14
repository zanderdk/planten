#ifndef SERVER_H
#define SERVER_H

#include "../led/EffectHandler.hpp"
#include "../command/CommandHandler.hpp"
// #include "CustomWebsocketHandler.hpp"

extern const char *SERVER_TAG;

void initialise_server(CommandHandler *);

#endif