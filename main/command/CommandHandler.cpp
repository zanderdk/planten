#include "CommandHandler.hpp"
#include "../led/rgb.hpp"

#include "../led/SolidEffect.hpp"
#include <memory>
#include "esp_log.h"

const char *COMMAND_HANDLER_TAG = "COMMAND_HANDLER";

void CommandHandler::handleCommand(std::string s) {
    std::shared_ptr<Command> cmd = makeCommand(s);

    ESP_LOGI(COMMAND_HANDLER_TAG, "handle command type: %s", cmd->type().c_str());
    
    if (cmd->type() == std::string("solid")) {
        SolidCommand *solid = static_cast<SolidCommand*>(cmd.get());
        ESP_LOGI(COMMAND_HANDLER_TAG, "color: %lf %lf %lf", solid->color.r, solid->color.g, solid->color.b);
        std::shared_ptr<Effect> se = std::make_shared<SolidEffect>
            (_led, _effectHandler->updateTime, solid->color);

        _effectHandler->setEffect(se);
    }
}

std::shared_ptr<Command> CommandHandler::makeCommand(std::string cmdStr) {

    cJSON *json = cJSON_Parse(cmdStr.c_str());
    cJSON *val;
    cJSON *type = cJSON_GetObjectItem(json, "type");


    std::string ty = std::string(type->valuestring);

    ESP_LOGI(COMMAND_HANDLER_TAG, "type: %s", ty.c_str());

    if(ty == std::string("solid")) {
            val = cJSON_GetObjectItem(json, "r");
            double r = val->valuedouble;
            val = cJSON_GetObjectItem(json, "g");
            double g = val->valuedouble;
            val = cJSON_GetObjectItem(json, "b");
            double b = val->valuedouble;
        
            rgb color{r, g, b};
            std::shared_ptr<SolidCommand> cmd = std::make_shared<SolidCommand>(color);

            return cmd;
    }

    rgb color{0, 0, 0};
    std::shared_ptr<SolidCommand> cmd = std::make_shared<SolidCommand>(color);
    return cmd;
}


std::shared_ptr<IRGB> CommandHandler::getLed() {
    return _led;
}