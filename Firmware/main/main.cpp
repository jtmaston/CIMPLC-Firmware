#include <modules/REPL.hpp>
#include <modules/networking.hpp>
#include <modules/http.hpp>
#include <modules/filesystem.hpp>
#include <init/serialInit.hpp>
#include <modules/gps.hpp>
#include <modules/twai.hpp>


Transport appInterconnect;
RTC_NOINIT_ATTR char rebootCounter;
RTC_NOINIT_ATTR char otaRebootAttemptCounter;

extern "C" {

int logToFile( const char *str, va_list l ) {
    return fprintf(appInterconnect.logfile, "%s", str);
}

static const char* TAG = "main";

void app_main() {

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    if (rebootCounter > 3 && rebootCounter < 10) {              // if three reboots have taken place
        if (otaRebootAttemptCounter < 3 ) {                     // check how many OTA attempts have taken place
            otaRebootAttemptCounter++;                          // increment them
            rebootCounter = 0;                                  // reboots must be reset
            esp_ota_mark_app_invalid_rollback_and_reboot();     // mark the partition as invalid and reboot
        }
        else                                                    // if more than 3 ota boot attempts have taken place
        {
            rebootCounter = 0;                                  // do a force reboot into the factory partition
            esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_APP,
                                                             ESP_PARTITION_SUBTYPE_APP_FACTORY,
                                                             "factory");
            const esp_partition_t *factory = esp_partition_get(pi);
            esp_partition_iterator_release(pi);
            esp_ota_set_boot_partition(factory);
            esp_restart();
        }
    }
    rebootCounter++;
    initFileSystem();
    initializeTWAIBus();

    wifiInitSoftAP();
    initializeREPL();
    setupHTTPServer();
    initializeSerialPorts();

    startParser();

    esp_ota_mark_app_valid_cancel_rollback();
}
}