//
// Created by Alexandru Anastasiu on 6/18/23.
//

#ifndef FIRMWARE_IOCONTROLLER_HPP
#define FIRMWARE_IOCONTROLLER_HPP

#include <cstdio>
#include "driver/i2c.h"
#include <esp_log.h>
#include <esp_adc/adc_continuous.h>
#include <esp_adc/adc_filter.h>
#include <soc/soc_caps.h>
#include "pca9555.hpp"
#include <cstring>

typedef enum
{
    PLC_NUM_1  = 20,                 // 21
    PLC_NUM_2  = 21,                 // 22
    PLC_NUM_3  = 22,                 // 23
    PLC_NUM_4  = 23,                 // 24
    PLC_NUM_5  = 24,                 // 25
    PLC_NUM_6  = 25,                 // 26
    PLC_NUM_7  = 26,                 // 27
    PLC_NUM_8  = 27,                 // 28
    PLC_NUM_9  = 28,                 // 29
    PLC_NUM_10 = 29,                 // 30
    PLC_NUM_11 = 10,                 // 11
    PLC_NUM_12 = 11,                 // 12
    PLC_NUM_13 = 12,                 // 13
    PLC_NUM_14 = 13,                 // 14
    PLC_NUM_15 = 29,                 // 15
    PLC_NUM_16 = 29,                 // 16
    PLC_NUM_17 = 29,                 // 17
    PLC_NUM_18 = 29,                 // 18
    PLC_NUM_19 = 29,                 // 19
    PLC_NUM_20 = 29,                 //

}plc_num_t;

class IOController
{
public:
    IOController();                                     // initializes the ADC
    ~IOController();

    void setPin(uint8_t pin, bool dir);                 // sets pin as either input or output, true = output
    bool digiRead(uint8_t pin);                         // reads a digital value from the pin
    uint16_t anaRead(uint8_t pin);                      // reads an analog value from the pin, 0-4096
    float anaReadVolts(uint8_t pin, float vcc = 3.3);   // reads an analog value and gives its voltage ref'd to vcc

    void digiWrite(plc_num_t pin, bool value);
    bool ready();

    void resetPins();                                   // sets all pins to inputs

private:
    uint32_t outputBuffer;                              // the state of the output pins
    uint32_t pinDir;                                    // the direction
    uint16_t analogValues[12] = {0};                    // the read analog values
    adc_continuous_handle_t driverHandle;               // handle of the ADC driver
    TaskHandle_t TaskHandle{};                          // handle of the polling Task

    static bool dataReadyNotifier( adc_continuous_handle_t handle,          // ISR to announce when the ADC can be read
                                   const adc_continuous_evt_data_t *edata,
                                   void *user_data);

    [[noreturn]] static void ioControllerTask(void* arg);   // the polling task
    pca9555* bank1;
    pca9555* bank2;


};



#endif //FIRMWARE_IOCONTROLLER_HPP
