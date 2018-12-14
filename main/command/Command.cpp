#include "Command.hpp"

std::string Command::type() {
    return "type";
}

std::string SolidCommand::type() {
    return "solid";
}