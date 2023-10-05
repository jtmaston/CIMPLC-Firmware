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

typedef struct {
    int pinNum = 0;
    int port = 1;
}plcPin_t;

// check the following pins:


#define PLC_O_1 plcPin_t (4, 1)
#define PLC_O_2 plcPin_t (5, 1)
#define PLC_O_3 plcPin_t (6, 1)
#define PLC_O_4 plcPin_t (7, 1)
#define PLC_O_5 plcPin_t (8, 1)
#define PLC_O_6 plcPin_t (9, 1)
#define PLC_O_7 plcPin_t (10, 1)
#define PLC_O_8 plcPin_t (11, 1)
#define PLC_O_9 plcPin_t (12, 1)
#define PLC_O_10 plcPin_t (13, 1)           // NOTE: due to reflow issues, pin 10 is unusable on the proto

#define PLC_IO_1 plcPin_t (10, 0)
#define PLC_IO_2 plcPin_t (11, 0)
#define PLC_O_11 plcPin_t (12, 0)           // NOTE: due to reflow issues, pin 11 is unusable on the proto
#define PLC_O_12 plcPin_t (13, 0)
#define PLC_O_13 plcPin_t (14, 0)
#define PLC_O_14 plcPin_t (15, 0)
#define PLC_O_15 plcPin_t (0, 1)
#define PLC_O_16 plcPin_t (1, 1)
#define PLC_O_17 plcPin_t (2, 1)
#define PLC_O_18 plcPin_t (3, 1)

#define PLC_IO_3 plcPin_t (0, 0)
#define PLC_IO_4 plcPin_t (1, 0)
#define PLC_IO_5 plcPin_t (2, 0)
#define PLC_IO_6 plcPin_t (3, 0)
#define PLC_IO_7 plcPin_t (4, 0)
#define PLC_IO_8 plcPin_t (5, 0)
#define PLC_IO_9 plcPin_t (6, 0)            // NOTE: due to assembly issues, IO9 is unusable on the proto
#define PLC_IO_10 plcPin_t (7, 0)
#define PLC_IO_11 plcPin_t (8, 0)           // we need a bloody oscilloscope on this, it's a hella signal
#define PLC_IO_12 plcPin_t (9, 0)


/*typedef enum
{


    PLC_O_1  = 20,                 // 21
    PLC_O_2  = 21,                 // 22
    PLC_O_3  = 22,                 // 23
    PLC_O_4  = 23,                 // 24
    PLC_O_5  = 24,                 // 25
    PLC_O_6  = 25,                 // 26
    PLC_O_7  = 26,                 // 27
    PLC_O_8  = 27,                 // 28
    PLC_O_9  = 28,                 // 29
    PLC_O_10 = 29,                 // 30
    PLC_NUM_11 = 10,                 // 11
    PLC_NUM_12 = 11,                 // 12
    PLC_NUM_13 = 12,                 // 13
    PLC_NUM_14 = 13,                 // 14
    PLC_NUM_15 = 29,                 // 15
    PLC_NUM_16 = 29,                 // 16
    PLC_NUM_17 = 29,                 // 17
    PLC_NUM_18 = 29,                 // 18
    PLC_NUM_19 = 29,                 // 19
    PLC_NUM_20 = 29,
    PLC_O_1 =

}plc_num_t;*/

class IOController
{
public:
    IOController();                                     // initializes the ADC
    ~IOController();

    void setPin(plcPin_t pin, bool dir);                 // sets pin as either input or output, true = output
    bool digiRead(plcPin_t pin);                         // reads a digital value from the pin
    uint16_t anaRead(plcPin_t pin);                      // reads an analog value from the pin, 0-4096
    float anaReadVolts(plcPin_t pin, float vcc = 3.3);   // reads an analog value and gives its voltage ref'd to vcc

    void digiWrite(plcPin_t pin, bool value);
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
