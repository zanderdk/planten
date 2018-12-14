#include "CustomWebSocetHandler.hpp"
#include "esp_log.h"

#include <sstream>

const char *SOCKET_TAG = "SOCKET_HANDLER";

void CustomWebsocketHandler::onMessage(WebSocketInputStreambuf* input, WebSocket* socket){
    std::ostringstream ss;
    ss << input;
    std::string s = ss.str();

    ESP_LOGI(SOCKET_TAG, "message: %s from: %s", s.c_str(), socket->getSocket().toString().c_str());
    _commandHandler->handleCommand(s);
    addSocket(socket);
}

void CustomWebsocketHandler::onError(std::string error){
    ESP_LOGE(SOCKET_TAG, "error: %s", error.c_str());
}
