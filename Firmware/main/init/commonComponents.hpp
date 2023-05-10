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

const char banner[] = TTY_ORANGE "██╗   ██╗██████╗ ██████╗     ██████╗ ██████╗ ██╗██╗   ██╗███████╗\n" TTY_DEFAULT
                      TTY_ORANGE "██║" TTY_DEFAULT "   ██║██╔══██╗██╔══██╗    ██╔══██╗██╔══██╗██║██║   ██║██╔══" TTY_ORANGE "══╝\n"
                      TTY_ORANGE "██║" TTY_DEFAULT "   ██║██████╔╝██████╔╝    ██║  ██║██████╔╝██║██║   ██║█████╗  \n"
                      TTY_ORANGE "██║" TTY_DEFAULT "   ██║██╔═══╝ ██╔══██╗    ██║  ██║██╔══██╗██║╚██╗ ██╔╝██╔══╝  \n"
                      TTY_ORANGE "╚██████╔╝██║     ██████╔╝    ██████╔╝██║  ██║██║ ╚████╔╝ ███████╗\n" TTY_DEFAULT
                      TTY_ORANGE " ╚═════╝ ╚═╝     ╚═════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝  ╚══════╝\n" TTY_DEFAULT;



#include <esp_http_server.h>
#include <sdmmc_cmd.h>
#include <esp_netif_types.h>
#include <linenoise/linenoise.h>
#include <esp_log.h>
#include <driver/uart.h>

struct gpsDataT
{
    float utcTime;
    int date;
    float latitude, longitude, altitude;
    bool fix;
    uint8_t satelliteCount;
    uint8_t satellitesInView;
    float groundSpeed;
    float heading;
};

struct sensorArrayData{
    float accX_;
    float accY_;
    float accZ_;

    float magX_;
    float magY_;
    float magZ_;

    float suspPotLeft_;
    float suspPotRight_;
};

class Transport
{
public:
    int sock;
    httpd_handle_t httpdServer;
    sdmmc_card_t *card;
    esp_netif_obj *iface;
    bool socketConnected = false;
    bool spiHasBeenInit = false;
    gpsDataT gpsData;
    FILE* stdioRedirect = stdout;
    bool debugPrintGPS = false;
    FILE* logfile;
    sensorArrayData front, rear;

};




#endif //SERIALTEST_COMMON_HPP
