//
// Created by Alexandru Anastasiu on 2/7/23.
//

#ifndef SERIALTEST_NETWORKING_HPP
#define SERIALTEST_NETWORKING_HPP

#include "init/commonComponents.hpp"
#include "modules/REPL.hpp"

#include <nvs_flash.h>
#include <lwip/sockets.h>
#include <esp_wifi.h>
#include "init/commonComponents.hpp"
#include <esp_ota_ops.h>
#include <esp_app_desc.h>
#include <esp_image_format.h>
#include <lwip/sockets.h>
#include <cmath>
httpd_handle_t setupHTTPServer();

void wifiInitSoftAP();
void tcpServerTask(void *pvParameters);
extern Transport appInterconnect;

#endif //SERIALTEST_NETWORKING_HPP
