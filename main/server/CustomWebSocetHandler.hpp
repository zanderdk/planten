#ifndef CUSTOMWEBSOCKETHANDLER_H
#define CUSTOMWEBSOCKETHANDLER_H

#include "HttpServer.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "../command/CommandHandler.hpp"
#include <vector>
#include "../led/IRGBSub.hpp"
#include "../utils.cpp"

#define responseTime (1000)

extern const char *SOCKET_TAG;

class CustomWebsocketHandler: public WebSocketHandler, public IRGBSub {

	public:
		CustomWebsocketHandler(CommandHandler *commandHandler): _commandHandler(commandHandler) {
			_led = commandHandler->getLed();
		}

		virtual void update(rgb color) override {

			if(getTimeFromStart() > lastUpdate + responseTime) {
				std::string str = "{\"type\": \"solid\", \"r\": ";
				str += to_string(color.r);
				str += ", \"g\": ";
				str += to_string(color.g);
				str += ", \"b\": ";
				str += to_string(color.b);
				str += "}";

				lastUpdate = getTimeFromStart();
			}
		}

	private:
		CommandHandler *_commandHandler;
		virtual void onMessage(WebSocketInputStreambuf* input, WebSocket* socket) override;
		virtual void onError(std::string error) override;
		unsigned int lastUpdate = 0;
		std::shared_ptr<IRGB> _led;

		WebSocket *_clients[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
		void addSocket(WebSocket *ptr) {
			for(int i = 0; i < 5; i++) {
				if (_clients[i] == ptr) {
					break;
				}
				if(_clients[i] == nullptr) {
					_clients[i] = ptr;
					break;
				}
			}
		}


		unsigned int getTimeFromStart() {
			return (unsigned int) (xTaskGetTickCount() * portTICK_PERIOD_MS);
		}
};

#endif