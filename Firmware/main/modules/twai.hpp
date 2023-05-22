//
// Created by aanas on 3/9/2023.
//

#ifndef CCU_TWAI_HPP
#define CCU_TWAI_HPP
#include "init/commonComponents.hpp"
#include <driver/gpio.h>
#include <driver/twai.h>

extern Transport appInterconnect;
void initializeTWAIBus();
int createTWAITask(int x, char**y);

[[noreturn]] void twaiTask(void *pvParameters);

#endif //CCU_TWAI_HPP
