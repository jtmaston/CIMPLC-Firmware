#include <nvs_flash.h>
#include <esp_wifi.h>
#include <esp_ota_ops.h>
#include <esp_image_format.h>
#include <esp_http_server.h>

void wifiInitSoftAP() {
    nvs_flash_init();
    ESP_ERROR_CHECK(esp_netif_init());
    esp_netif_create_default_wifi_ap();

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
    esp_wifi_start();
}


extern const char uploadWebpageStart[] asm ("_binary_upload_html_start");

esp_err_t renderUploadPage(httpd_req_t *req) {
    return httpd_resp_send(req, uploadWebpageStart, HTTPD_RESP_USE_STRLEN);
}

esp_err_t renderUploadPagePOST(httpd_req_t *req) {
    char buf[8192];
    int32_t received;
    uint32_t totalReceived = 0;
    esp_ota_handle_t updateHandle = 0;
    const esp_partition_t *updatePartition = nullptr;
    bool magicPacketVerified = false;

    if (req->content_len == 0) {
        fflush(stdout);
        return ESP_ERR_NOT_FINISHED;
    }

    while (totalReceived < req->content_len) {
        memset(buf, 0, sizeof(buf));
        received = httpd_req_recv(req, buf, sizeof(buf));
        if (received > 0) {
            if (!magicPacketVerified) {
                if (received >
                    sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t) + sizeof(esp_app_desc_t)) {
                    // check current version with downloading
                    if ((int) buf[0] != 0xE9) {
                        return ESP_ERR_OTA_VALIDATE_FAILED;
                    } else {
                        updatePartition = esp_ota_get_next_update_partition(nullptr);
                        int ret = esp_ota_begin(updatePartition, OTA_SIZE_UNKNOWN, &updateHandle);
                        esp_ota_write(updateHandle, buf, received);
                        magicPacketVerified = true;
                        totalReceived += received;
                    }
                }
            } else {
                esp_ota_write(updateHandle, buf, received);
                totalReceived += received;
            }

        } else {
            esp_ota_end(updateHandle);
            return ESP_ERR_OTA_VALIDATE_FAILED;
        }
    }

    esp_ota_end(updateHandle);
    ESP_ERROR_CHECK(esp_ota_set_boot_partition(updatePartition));

    esp_restart();
}

httpd_uri_t mainPageUri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = renderUploadPage,
        .user_ctx = nullptr};

httpd_uri_t mainPageUriPOST = {
        .uri = "/",
        .method = HTTP_POST,
        .handler = renderUploadPagePOST,
        .user_ctx = nullptr};



httpd_handle_t setupHTTPServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 3072 + 8192 + 512;              // 3072: for functionality ; 4096 for packet stack and 256 for
    httpd_handle_t server = nullptr;                    // verification headroom

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &mainPageUri);
        httpd_register_uri_handler(server, &mainPageUriPOST);
    }
    return server;
}


extern "C"{

void app_main() {

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifiInitSoftAP();
    setupHTTPServer();

}
}

/*
 * # Name,Type,SubType,Offset,Size,Flags
nvs,data,nvs,0x9000,0x4000,
otadata,data,ota,0xd000,0x2000,
phy_init,data,phy,0xf000,0x1000,
factory,app,factory,,500K,
ota_0,app,ota_0,,1700K,
ota_1,app,ota_1,,1700K,
 */