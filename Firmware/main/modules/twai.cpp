//
// Created by aanas on 3/9/2023.
//

#include "twai.hpp"
#include "hal/twai_types.h"

int createTWAITask(int x, char**y)
{
    xTaskCreate(twaiTask,
                "twai",
                2048,
                nullptr,
                tskIDLE_PRIORITY,
                nullptr);
    return 0;
}

#include <array>
[[noreturn]] void twaiTask(void *pvParameters)
{
    //stdout = appInterconnect.stdioRedirect;

    // [ID] [ ] [ ] [ ] ...
    while(true)
    {
        twai_message_t msg;

        auto returnCode = twai_receive(&msg, pdMS_TO_TICKS(1000));

        switch(returnCode)
        {
            case ESP_OK:
            {
                switch(msg.identifier)
                {
                    case 0x6:
                    {
                        appInterconnect.front.accX_ = (float)(int16_t (msg.data[0]) << 8 | int16_t(msg.data[ 1 ])) / 100.0f;
                        appInterconnect.front.accY_ = (float)(int16_t (msg.data[2]) << 8 | int16_t(msg.data[ 3 ])) / 100.0f;
                        appInterconnect.front.accZ_ = (float)(int16_t (msg.data[4]) << 8 | int16_t(msg.data[ 5 ])) / 100.0f;

                        appInterconnect.front.suspPotLeft_ = (float)(((int16_t) msg.data[6]) << 8 | msg.data[ 7 ]) / 100.0f;
                        //printf("%hd\n", (int16_t (msg.data[4]) << 8 | int16_t(msg.data[ 5 ])));
                        //printf("%f %f %f %f\n", appInterconnect.front.accX_, appInterconnect.front.accY_, appInterconnect.front.accZ_,
                        //       appInterconnect.front.suspPotLeft_);
                        //fflush(stdout);
                        break;
                    }
                    case 0x7:
                    {
                        appInterconnect.front.magX_ = (float)(int16_t (msg.data[0]) << 8 | msg.data[ 1 ]) / 100.0f;
                        appInterconnect.front.magX_ = (float)(int16_t (msg.data[2]) << 8 | msg.data[ 3 ]) / 100.0f;
                        appInterconnect.front.magX_ = (float)(int16_t (msg.data[4]) << 8 | msg.data[ 5 ]) / 100.0f;

                        appInterconnect.front.suspPotRight_ = (float)(int16_t (msg.data[6]) << 8 | msg.data[ 7 ]) / 100;
                        break;
                    }
                }

                break;
            }
            case ESP_ERR_TIMEOUT:
            {
                printf("Timeout!\n");
                fflush(stdout);
                break;
            }
            case ESP_ERR_INVALID_ARG:
            {
                printf("Invalid args!");
                fflush(stdout);
                break;
            }
            case ESP_ERR_INVALID_STATE:
            {
                printf("Invalid state!");
                fflush(stdout);
                break;
            }

        }

    }
}

void initializeTWAIBus()
{
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_15, GPIO_NUM_2, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
        printf("Driver installed\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }

    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }
    //xTaskCreate(twaiTask, "twai", 2048, nullptr, tskIDLE_PRIORITY, nullptr);
}