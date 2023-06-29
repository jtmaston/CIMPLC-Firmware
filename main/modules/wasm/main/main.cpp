#include <stdio.h>
#include <string.h>
#include <wasm3/source/wasm3.h>
#include "wasm3/source/m3_function.h"
#include <hal/gpio_types.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wasm.hpp"
#include <wasm3/source/m3_env.h>
#include <driver/gpio.h>
#include "include/upload.h"

#define NATIVE_STACK_SIZE   (32*1024)
#define WASM_STACK_SLOTS    1024
#define WASM_MEMORY_LIMIT   2048 * 5                        // apparently, WASM needed more memory, which was causing
// the crash
extern "C" {

static const char *TAG = "main";

extern const char uploadWebpageStart[] asm ("_binary_upload_html_start");

const char *filename = "../WasmPrograms/target.wasm";

httpd_handle_t serv;

gpio_num_t iPorts[] = {GPIO_NUM_36, GPIO_NUM_39, GPIO_NUM_34, GPIO_NUM_35, GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_25,
                       GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_12, GPIO_NUM_13};
gpio_num_t oPorts[] = {GPIO_NUM_0, GPIO_NUM_10, GPIO_NUM_11};

m3ApiRawFunction(m3_IO_getpin) {
    m3ApiReturnType(uint32_t)
    m3ApiGetArg(uint32_t, pinNumber)
    uint32_t pinStat = gpio_get_level(iPorts[pinNumber]);
    m3ApiReturn(pinStat)
}

m3ApiRawFunction(m3_IO_setpin) {
    m3ApiGetArg(uint32_t, pinNumber)
    m3ApiGetArg(uint32_t, stat)
    gpio_set_level(oPorts[pinNumber], stat);
    m3ApiSuccess()
}

M3Result linkESP(IM3Runtime rt) {
    IM3Module module = rt->modules;
    m3_LinkRawFunction(module, "IO", "getpin", "i(i)", &m3_IO_getpin);
    m3_LinkRawFunction(module, "IO", "setpin", "v(ii)", &m3_IO_setpin);
    return m3Err_none;
}


void wasm_task(void *pvParameters) {
    M3Result result = m3Err_none;

    IM3Environment env = m3_NewEnvironment();
    if (!env) printf("NewEnvironment failed");

    IM3Runtime runtime = m3_NewRuntime(env, WASM_STACK_SLOTS, NULL);
    if (!runtime) printf("NewRuntime failed");

#ifdef WASM_MEMORY_LIMIT
    runtime->memoryLimit = WASM_MEMORY_LIMIT;
#endif

    IM3Module module;
    result = m3_ParseModule(env, &module, target_wasm, target_wasm_len);
    if (result) printf("Problem parsing module");
    result = m3_LoadModule(runtime, module);
    if (result) printf("Problem loading module");

    result = linkESP(runtime);
    if (result) printf("Problem linking ESP");

    IM3Function f;
    result = m3_FindFunction(&f, runtime, "run");
    if (result) printf("Problem finding function");

    printf("Loading Web Ass...");
    fflush(stdout);
    result = m3_CallV(f);

    printf("After function call");
    fflush(stdout);

    if (result) {
        M3ErrorInfo info;
        m3_GetErrorInfo(runtime, &info);
        printf("Error: ");
        if (info.file && strlen(info.file) && info.line) {
            printf("aici");
        }
    }

    vTaskDelete(nullptr);                               // make sure to delete the task on exit, otherwise the dreaded
}// "guru meditation error" will pop up

esp_err_t renderUploadPage(httpd_req_t *req) {
    return httpd_resp_send(req, uploadWebpageStart, HTTPD_RESP_USE_STRLEN);
}

esp_err_t post_handler(httpd_req_t *req)
{
    return ESP_OK;
}


httpd_uri_t mainPageUri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = renderUploadPage,
        .user_ctx = nullptr};

httpd_uri_t mainPageUriPOST = {
        .uri      = "/uri",
        .method   = HTTP_POST,
        .handler  = post_handler,
        .user_ctx = NULL
};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
#if CONFIG_IDF_TARGET_LINUX
    // Setting port as 8001 when building for Linux. Port 80 can be used only by a priviliged user in linux.
    // So when a unpriviliged user tries to run the application, it throws bind error and the server is not started.
    // Port 8001 can be used by an unpriviliged user as well. So the application will not throw bind error and the
    // server will be started.
    config.server_port = 8001;
#endif // !CONFIG_IDF_TARGET_LINUX
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &mainPageUri);
//        httpd_register_uri_handler(server, &echo);
//        httpd_register_uri_handler(server, &ctrl);
#if CONFIG_EXAMPLE_BASIC_AUTH
        httpd_register_basic_auth(server);
#endif
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void app_main() {
    printf("In app main");
    fflush(stdout);
//    xTaskCreate(                                        // app_main should be called only for initialization,
//            wasm_task,                              // as such it is limited in stack size
//            "Wasm Task",   // bigger stack sizes require other tasks to be used
//            NATIVE_STACK_SIZE,
//            NULL,
//            tskIDLE_PRIORITY,
//            NULL
//    );
    wifiInitSoftAP();
    start_webserver();
    printf("Done task creating");
    fflush(stdout);

}

}