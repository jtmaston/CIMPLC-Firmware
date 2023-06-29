#include <modules/REPL.hpp>
#include <modules/networking.hpp>
#include <modules/filesystem.hpp>
#include <modules/twai.hpp>
#include <modules/IOController.hpp>
#include <mutex>
#include "driver/i2c.h"


std::mutex M_MUTEX_PROTECTOR;
Transport appInterconnect;

__NOINIT_ATTR char rebootCounter;
__NOINIT_ATTR int firstBoot;
RTC_NOINIT_ATTR int wearLevelAddress;

extern "C" {

static const char* TAG = "main";

#define TIME_FUNCTION(function) uint64_t start = esp_timer_get_time(); function; uint64_t end = esp_timer_get_time(); printf("%llu ms passed\n", (end - start) / 1000); fflush(stdout);

void blinker(void *arg) {

    while(!appInterconnect.ctrl.ready()){}  // block until the remote I/O's initialize

    plc_num_t pin = PLC_NUM_13;

    while(true) {

        appInterconnect.ctrl.digiWrite(pin, true);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        appInterconnect.ctrl.digiWrite(pin, false);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);

}

void app_main() {

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_18, true);
    gpio_set_level(GPIO_NUM_19, false);

    //vTaskDelay(500);
    //appInterconnect.ctrl.digiWrite(PIN_1, true);

    /*if(firstBoot != 2306){
        firstBoot = 2306;
        rebootCounter = 0;
    }
    printf("RebootCounter: %d\n", rebootCounter);
    fflush(stdout);

    if (rebootCounter > 3) {              // if three reboots have taken place
         // do a force reboot into the factory partition
        printf("Doing a reboot, since rebootCounter is %d", rebootCounter);
        fflush(stdout);
        rebootCounter = 0;
        esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_APP,
                                                         ESP_PARTITION_SUBTYPE_APP_FACTORY,
                                                         "factory");
        const esp_partition_t *factory = esp_partition_get(pi);
        esp_partition_iterator_release(pi);
        esp_ota_set_boot_partition(factory);
        esp_restart();

    }
    rebootCounter++;

    wifiInitSoftAP();
    setupHTTPServer();
    initializeREPL();

    initFileSystem();
    initializeTWAIBus();
    //initializeSerialPorts();*/


    //esp_ota_mark_app_valid_cancel_rollback();
    xTaskCreate(&blinker, "eeprom_read_write_demo", 8192 * 2, nullptr, tskIDLE_PRIORITY, nullptr);
    rebootCounter = 0;
}
}