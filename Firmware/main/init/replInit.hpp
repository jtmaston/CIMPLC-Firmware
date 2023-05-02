//
// Created by Alexandru Anastasiu on 1/29/23.
//

#ifndef SERIALTEST_REPLINIT_HPP
#define SERIALTEST_REPLINIT_HPP

#include <esp_console.h>
#include "lwip/sockets.h"
#include <esp_netif.h>
#include <linenoise/linenoise.h>
#include <esp_log.h>

esp_console_repl_t *repl = nullptr;


void initializeRepl()
{
    //esp_console_repl_config_t replConfig = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_config_t a = ESP_CONSOLE_CONFIG_DEFAULT();
    //replConfig.prompt = "CCU >";
    //replConfig.max_cmdline_length = 1024U;

    ESP_ERROR_CHECK(esp_console_register_help_command());
    esp_console_init(&a);

    //esp_console_dev_uart_config_t hwConfig = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    //esp_console_new_repl_uart(&hwConfig, &replConfig, &repl);


}


#endif //SERIALTEST_REPLINIT_HPP
