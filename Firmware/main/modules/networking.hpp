//
// Created by Alexandru Anastasiu on 2/7/23.
//

#ifndef SERIALTEST_NETWORKING_HPP
#define SERIALTEST_NETWORKING_HPP

#include <init/commonComponents.hpp>
#include <modules/REPL.hpp>

#include <nvs_flash.h>
#include <lwip/sockets.h>
#include <esp_wifi.h>


void wifiInitSoftAP();
void tcpServerTask(void *pvParameters);
extern Transport appInterconnect;

#endif //SERIALTEST_NETWORKING_HPP
