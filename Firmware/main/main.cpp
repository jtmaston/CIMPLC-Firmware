#include <modules/REPL.hpp>
#include <modules/networking.hpp>
#include <modules/filesystem.hpp>
#include <modules/twai.hpp>
#include "driver/i2c.h"


Transport appInterconnect;
__NOINIT_ATTR char rebootCounter;
__NOINIT_ATTR int firstBoot;
RTC_NOINIT_ATTR int wearLevelAddress;

extern "C" {

static const char* TAG = "main";

void pula(void *pvParameters)
{
    uint8_t i = 0;
    while(true)
    {
        uint8_t data;
        uint8_t byte = i2c_master_write_read_device(I2C_NUM_0, 0x50, &data, 1, &data, sizeof(uint8_t), 1000 / portTICK_PERIOD_MS);
        printf("0x%x: 0x%x ",i, byte);
        fflush(stdout);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i++;
    }
}

void app_main() {

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    if(firstBoot != 2306){
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

    /*initFileSystem();
    initializeTWAIBus();
    //initializeSerialPorts();*/

    xTaskCreate(pula, "pulaTask", 8192, nullptr, tskIDLE_PRIORITY, nullptr);

    esp_ota_mark_app_valid_cancel_rollback();
    rebootCounter = 0;
}
}