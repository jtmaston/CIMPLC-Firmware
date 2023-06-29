//
// Created by mihai on 29.06.23.
//

#include <nvs_flash.h>
#include <esp_wifi.h>
#include <esp_ota_ops.h>
#include <esp_image_format.h>
#include <esp_http_server.h>
#include <esp_log.h>

#ifndef WASMLIB_UPLOAD_H
#define WASMLIB_UPLOAD_H

#endif //WASMLIB_UPLOAD_H

esp_netif_obj * a;

void wifiInitSoftAP() {

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    a = esp_netif_create_default_wifi_ap();


    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifiConfig =
            {
                    .ap = {
                            .ssid = "PLC",
                            .ssid_len = 3U,
                            .channel = 10U,
                            .authmode = WIFI_AUTH_OPEN,
                            .max_connection = 2U,
                    },
            };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifiConfig);
    ESP_ERROR_CHECK(esp_wifi_start());

}
