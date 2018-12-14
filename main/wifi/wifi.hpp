#ifndef WIFI_H
#define WIFI_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_err.h"
#include "esp_http_client.h"
#include "esp_event_loop.h"

extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

extern const char *OTA_TAG;
extern EventGroupHandle_t wifi_event_group;
extern const int CONNECTED_BIT;

esp_err_t _http_event_handler(esp_http_client_event_t *evt);
esp_err_t event_handler(void *ctx, system_event_t *event);
void initialise_wifi(void);
void ota_task(void * pvParameter);
#endif // WIFI_H