//
// Created by Alexandru Anastasiu on 2/7/23.
//

#include "http.hpp"

#include <freertos/task.h>

extern const char webpageStart[] asm ("_binary_main_html_start");
extern const char uploadWebpageStart[] asm ("_binary_upload_html_start");

esp_err_t renderStatsPage(httpd_req_t *req) {
    return httpd_resp_send(req, webpageStart, HTTPD_RESP_USE_STRLEN);
}

esp_err_t renderUploadPage(httpd_req_t *req) {
    return httpd_resp_send(req, uploadWebpageStart, HTTPD_RESP_USE_STRLEN);
}

esp_err_t doEmgReboot(httpd_req_t *req) {
    esp_restart();
}

esp_err_t renderUploadPagePOST(httpd_req_t *req) {
    char buf[4096];
    int32_t received;
    uint32_t totalReceived = 0;
    esp_ota_handle_t updateHandle = 0;
    const esp_partition_t *updatePartition = nullptr;
    bool magicPacketVerified = false;

    stdout = appInterconnect.stdioRedirect;
    auto h = xTaskGetHandle("telnet_repl");
    if(h != nullptr)
        vTaskDelete(h);
    h = xTaskGetHandle("GPS_Parser");
    if(h != nullptr)
        vTaskDelete(h);
    h = xTaskGetHandle("telnetListener");
    if(h != nullptr)
        vTaskDelete(h);
    h = xTaskGetHandle("top");
    if(h != nullptr)
        vTaskDelete(h);

    linenoiseClearScreen();
    printf("OTA Update started...\n");
    fflush(stdout);

    if (req->content_len == 0) {
        printf("Update failed! No data was received!\n");
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
                    esp_app_desc_t updateInfo;
                    memcpy(&updateInfo,
                           &buf[sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t)],
                           sizeof(esp_app_desc_t));
                    printf("New firmware version: %s\n", updateInfo.version);

                    esp_app_desc_t runningAppInfo;
                    if (esp_ota_get_partition_description(esp_ota_get_running_partition(), &runningAppInfo) == ESP_OK) {
                        printf("Running firmware version: %s\n", runningAppInfo.version);
                    }

                    if ((int) buf[0] != 0xE9) {
                        char err[] = "Magic byte not found!";
                        httpd_resp_send(req, err, sizeof(err));
                        printf("Magic byte was not found!\n");
                        fflush(stdout);
                        return ESP_ERR_OTA_VALIDATE_FAILED;
                    } else {
                        updatePartition = esp_ota_get_next_update_partition(nullptr);
                        if (updatePartition == nullptr) {
                            char err[] = "No available OTA partition!";
                            httpd_resp_send(req, err, sizeof(err));
                            printf("No available OTA partition!\n");
                            fflush(stdout);
                            return ESP_ERR_OTA_PARTITION_CONFLICT;
                        }
                        int ret = esp_ota_begin(updatePartition, OTA_SIZE_UNKNOWN, &updateHandle);
                        if(ret != ESP_OK) {
                            printf("Could NOT start OTA update! This may indicate a hardware failure! Please reformat using idf.py erase and try again.");
                            fflush(stdout);
                        }

                        esp_ota_write(updateHandle, buf, received);
                        magicPacketVerified = true;
                        totalReceived += received;
                    }
                }
            } else {
                printf("\r %d %%", (int) std::floor((float) totalReceived / (float) req->content_len * 100));
                fflush(stdout);
                esp_ota_write(updateHandle, buf, received);
                totalReceived += received;
            }

        } else {
            printf("\nUpload has failed!\n");
            fflush(stdout);
            esp_ota_end(updateHandle);
            return ESP_ERR_OTA_VALIDATE_FAILED;
        }
    }

    extern unsigned int rebootCounter;
    extern unsigned int otaRebootAttemptCounter;
    rebootCounter = 0;
    otaRebootAttemptCounter = 0;

    printf("\nUpload complete!\n");
    fflush(stdout);
    esp_ota_end(updateHandle);
    ESP_ERROR_CHECK(esp_ota_set_boot_partition(updatePartition));
    printf("Restarting...");
    fflush(stdout);

    close(appInterconnect.sock);



    esp_restart();
}

httpd_uri_t statsPageUri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = renderStatsPage,
        .user_ctx = nullptr};

httpd_uri_t uploadsPageUri = {
        .uri = "/upload",
        .method = HTTP_GET,
        .handler = renderUploadPage,
        .user_ctx = nullptr};

httpd_uri_t uploadsPagePostUri = {
        .uri = "/upload",
        .method = HTTP_POST,
        .handler = renderUploadPagePOST,
        .user_ctx = nullptr};

httpd_uri_t rebootPagePOSTUri = {
        .uri = "/reboot",
        .method = HTTP_POST,
        .handler = doEmgReboot,
        .user_ctx = nullptr};

httpd_uri_t rebootPageGETUri = {
        .uri = "/reboot",
        .method = HTTP_GET,
        .handler = doEmgReboot,
        .user_ctx = nullptr};

char buffer[200] = "";
esp_err_t sendData(httpd_req_t *req) {
    stdout = appInterconnect.stdioRedirect;
    sprintf(buffer, "%f %d %f %f %d %f %f %f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f",
            appInterconnect.gpsData.utcTime,
            appInterconnect.gpsData.date,
            appInterconnect.gpsData.latitude,
            appInterconnect.gpsData.longitude,
            appInterconnect.gpsData.satellitesInView,
            appInterconnect.gpsData.heading,
            appInterconnect.gpsData.altitude,
            appInterconnect.gpsData.groundSpeed,
            appInterconnect.front.accX_,
            appInterconnect.front.accY_,
            appInterconnect.front.accZ_,
            appInterconnect.front.magX_,
            appInterconnect.front.magY_,
            appInterconnect.front.magZ_,
            appInterconnect.front.suspPotLeft_,
            appInterconnect.front.suspPotRight_
            );
    //printf("%s\n", buffer);
    //fflush(stdout);

    return httpd_resp_send(req, buffer, HTTPD_RESP_USE_STRLEN);

}

httpd_uri_t dataPageGETUri = {
        .uri = "/data",
        .method = HTTP_GET,
        .handler = sendData,
        .user_ctx = nullptr};

httpd_handle_t setupHTTPServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 3072 + 4096 + 512;              // 3072: for functionality ; 4096 for packet stack and 256 for
    httpd_handle_t server = nullptr;                    // verification headroom

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &statsPageUri);
        httpd_register_uri_handler(server, &uploadsPageUri);
        httpd_register_uri_handler(server, &uploadsPagePostUri);
        httpd_register_uri_handler(server, &rebootPagePOSTUri);
        httpd_register_uri_handler(server, &rebootPageGETUri);
        httpd_register_uri_handler(server, &dataPageGETUri);
    }
    appInterconnect.httpdServer = server;
    return server;
}