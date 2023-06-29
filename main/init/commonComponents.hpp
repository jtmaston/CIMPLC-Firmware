//
// Created by Alexandru Anastasiu on 2/7/23.
//



#ifndef SERIALTEST_COMMON_HPP
#define SERIALTEST_COMMON_HPP

#define TTY_ORANGE  "\033[38;5;208m"
#define TTY_GREEN  "\033[38;5;46m"
#define TTY_RED  "\033[38;5;196m"
#define TTY_DEFAULT "\033[m"
#define PORT_TICK_PERIOD_MS portTICK_PERIOD_MS

#define LORA_SERIAL UART_NUM_1
#define GPS_SERIAL UART_NUM_2
#include <rtc.h>

const char banner[]    = " ██████╗██╗███╗   ███╗      ██████╗ ██╗      ██████╗\n"
                         "██╔════╝██║████╗ ████║      ██╔══██╗██║     ██╔════╝\n"
                         "██║     ██║██╔████╔██║█████╗██████╔╝██║     ██║     \n"
                         "██║     ██║██║╚██╔╝██║╚════╝██╔═══╝ ██║     ██║     \n"
                         "╚██████╗██║██║ ╚═╝ ██║      ██║     ███████╗╚██████╗\n"
                         " ╚═════╝╚═╝╚═╝     ╚═╝      ╚═╝     ╚══════╝ ╚═════╝\n"
                         "                                                    ";



#include <esp_http_server.h>
#include <sdmmc_cmd.h>
#include <esp_netif_types.h>
#include <linenoise/linenoise.h>
#include <esp_log.h>
#include <driver/uart.h>
#include "eeprom.hpp"
#include <modules/IOController.hpp>

#define TIME_FUNCTION(function) uint64_t start = esp_timer_get_time(); function; uint64_t end = esp_timer_get_time(); printf("%llu ms passed\n", (end - start) / 1000); fflush(stdout);

struct Transport
{
    int sock;
    httpd_handle_t httpdServer;
    sdmmc_card_t *card;
    esp_netif_obj *iface;
    bool socketConnected = false;
    FILE* stdioRedirect = stdout;
    bool debugPrintGPS = false;
    FILE* logfile;
    #define BUILD_DEBUG             // this restricts our operations to the top 0x1000 bytes of the eeprom, to minimize wear
                                    // further

#ifdef BUILD_DEBUG
    //EEPROM eeprom = EEPROM(0x50, 0x0, 0x1000, 256, true);
#else
    EEPROM eeprom = EEPROM(0x50, 0x0, 256 * 1024, 256, true);
#endif

    IOController ctrl;



};




#endif //SERIALTEST_COMMON_HPP
