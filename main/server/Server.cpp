#include "Server.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "../wifi/wifi.hpp"
#include "esp_log.h"
#include "HttpServer.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "File.h"
#include <FileSystem.h>

#include "CustomWebSocetHandler.hpp"

#include <map>

const char *SERVER_TAG = "SERVER";

void handle_root(HttpRequest* pRequest, HttpResponse* pResponse) {
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/html");

    // Open renamed file for reading
    File f{"/spiffs/index.html"};
    ESP_LOGI(SERVER_TAG, "Reading file");
    std::string data = f.getContent();
    ESP_LOGI(SERVER_TAG, "Read from file: '%s'", data.c_str());

    pResponse->sendData(data);
    pResponse->close();
}

void deleteFile(HttpRequest* pRequest, HttpResponse* pResponse) {
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");

    std::map<std::string, std::string> params = pRequest->getQuery();

    std::string path = "/spiffs/";
    std::string name = params[std::string("name")];
    path += name;

    ESP_LOGI(SERVER_TAG, "removing file: %s", path.c_str());

    FileSystem::remove(path);

    pResponse->sendData("OK");
    pResponse->close();
}

void upload(HttpRequest* pRequest, HttpResponse* pResponse) {
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");

    // Open renamed file for reading
    std::string data = pRequest->getBody();
    int index = data.find("filename=\"") + 10;
    int lastIndex = data.find("\"", index);
    std::string name = data.substr(index, lastIndex - index);

    ESP_LOGI(SERVER_TAG, "name: (%d, %d) %s", index, lastIndex, name.c_str());

    std::string path{"/spiffs/"};
    path.append(name);

    ESP_LOGI(SERVER_TAG, "saving to: %s", path.c_str());

    int boundIndex = data.find("\n") - 1;
    std::string bound = data.substr(0, boundIndex);

    ESP_LOGI(SERVER_TAG, "bound: (%d, %d) %s", 0, boundIndex, bound.c_str());
    // ESP_LOGI(SERVER_TAG, "data: \n%s", data.c_str());

    int dataFirstIndex = data.find("\n\n");
    int indexOffset = 2;
    std::string searchStr = "\n\r\n";

    if (dataFirstIndex == -1) {
        dataFirstIndex = data.find("\r\n\r\n");
        indexOffset = 4;
    }

    int dataLastIndex = data.find(bound.substr(0, bound.size() - 1), dataFirstIndex);

    // ESP_LOGI(SERVER_TAG, "file index: (%d, %d)", dataFirstIndex, dataLastIndex);
    
    std::string fileContent = data.substr(dataFirstIndex, dataLastIndex - dataFirstIndex);
    fileContent = fileContent.substr(indexOffset, fileContent.rfind(searchStr.c_str()) - indexOffset );

    ESP_LOGI(SERVER_TAG, "file:\n%s", fileContent.c_str());

    ESP_LOGI(SERVER_TAG, "Opening file");
    FILE* f = fopen(path.c_str(), "w");
    if (f == NULL) {
        ESP_LOGE(SERVER_TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, fileContent.c_str());
    fclose(f);
    ESP_LOGI(SERVER_TAG, "File written");

    pResponse->sendData("OK");
    pResponse->close();
}

WebSocketHandler *socketHandler;

void web_socket(HttpRequest* pRequest, HttpResponse* pResponse) {
    if (!pRequest->isWebsocket()) {
        pResponse->setStatus(HttpResponse::HTTP_STATUS_BAD_REQUEST, "FAIL");
        pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
        pResponse->sendData("FAIL");
        pResponse->close();
        return;
    }
    WebSocket *socket = pRequest->getWebSocket();
    socket->setHandler(socketHandler);
}

void initialise_server(CommandHandler *customHandler) {
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);
    ESP_LOGI(SERVER_TAG, "Connected to Wifi. Starting web server");

    HttpServer* pHttpServer = new HttpServer();
    // socketHandler = customHandler;
    pHttpServer->addPathHandler(HttpRequest::HTTP_METHOD_POST, "/upload", upload);

    std::regex *deleteReg = new std::regex("delete.*");
    pHttpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, deleteReg, deleteFile);
    pHttpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, "/", handle_root);
    pHttpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, "/websocket", web_socket);
    pHttpServer->start(80);
}