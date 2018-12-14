#include "esp_err.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "led/led.hpp"
#include "wifi/wifi.hpp"
#include <memory>
#include "esp_log.h"

#include "led/Effect.hpp"
#include "led/SolidEffect.hpp"
#include "led/FadeEffect.hpp"
#include "led/EffectHandler.hpp"
#include "server/Server.hpp"

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_spiffs.h"
// #include "./server/CustomWebSocetHandler.hpp"

#define ledUpdateTime (500)

extern "C" {
   void app_main();
}

static const char *SPIFFS_TAG = "SPIFFS init";

std::shared_ptr<IRGB> led{ new RGBLed{} };
EffectHandler effectHandler{ledUpdateTime};

uint32_t getTimeSinceStart() {
     return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS);
 }

void led_task(void * pvParameter) {
    ESP_LOGI(LED_TAG, "led task started");
    for(;;) {
        effectHandler.update(getTimeSinceStart());
        vTaskDelay(ledUpdateTime / portTICK_PERIOD_MS);
    }
}

void initialise_spiffs() {
    ESP_LOGI(SPIFFS_TAG, "Initializing SPIFFS");
    
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };
    

    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(SPIFFS_TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(SPIFFS_TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(SPIFFS_TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(SPIFFS_TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(SPIFFS_TAG, "Partition size: total: %d, used: %d", total, used);
    }
}

void app_main()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    initialise_wifi();
    initialise_spiffs();

    std::shared_ptr<Effect> se = std::make_shared<FadeEffect>(led, ledUpdateTime, 5000, 5000);
    effectHandler.setEffect(se);

    CommandHandler *commandHandler = new CommandHandler(&effectHandler, led);
    initialise_server(commandHandler);

    xTaskCreate(&ota_task, "ota_task", 8192, NULL, 5, NULL);
    xTaskCreate(&led_task, "led_task", 8192, NULL, 5, NULL);
}
