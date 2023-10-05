//
// Created by Alexandru Anastasiu on 6/18/23.
//

#include "IOController.hpp"

bool IRAM_ATTR IOController::dataReadyNotifier(                 // this is an ISR to ensure that ADC data is not read
        adc_continuous_handle_t handle,                         // before it is available in the ADC
        const adc_continuous_evt_data_t *edata,                 // it will issue a notification when data can be read
        void *user_data) {

    auto *parent = (IOController *) user_data;
    BaseType_t mustYield = pdFALSE;
    vTaskNotifyGiveFromISR(parent->TaskHandle, &mustYield);

    return (mustYield == pdTRUE);
}

[[noreturn]] void IOController::ioControllerTask(void *arg)     // this task constantly polls the ADC and stores the
{                                                               // values into the incoming array
    auto *ctrl = (IOController *) arg;
    uint8_t data[256] = {0};                                    // todo: check if the size of this can be reduced
    uint32_t ret_num = 0;                                       // number of bytes returned

    ctrl->bank1 = new pca9555(0x26, true);
    ctrl->bank2 = new pca9555(0x27);


    while (true)                                                 // in an infinite loop
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);                 // block until the ADC data is ready
        esp_err_t ret = adc_continuous_read(ctrl->driverHandle, data, 256, &ret_num, 0);    // then read it
        switch (ret) {                                           // if it is ok, write it to the adc array
            case ESP_OK: {
                for (int i = 0; i < ret_num; i += SOC_ADC_DIGI_RESULT_BYTES) {
                    auto *p = (adc_digi_output_data_t *) &data[i];
                    ctrl->analogValues[p->type1.channel] = p->type1.data;
                }
                break;
            }
            default:                                             // if not, log an error
            {
                printf("%s", esp_err_to_name(ret));
                fflush(stdout);
            }
        }
    }

}

IOController::IOController() {                                   // initializes the controller

    this->outputBuffer = 0;
    this->pinDir = 0;
    this->driverHandle = nullptr;

    static adc_channel_t channels[] = {ADC_CHANNEL_0,            // select which channels of the ADC will be used
                                       ADC_CHANNEL_1,
                                       ADC_CHANNEL_2,
                                       ADC_CHANNEL_3,
                                       ADC_CHANNEL_4,
                                       ADC_CHANNEL_5,
                                       ADC_CHANNEL_6,
                                       ADC_CHANNEL_7,
                                       ADC_CHANNEL_8,
                                       ADC_CHANNEL_9
    };

    adc_continuous_handle_cfg_t handleCfg                        // and set the buffers to sizes alloted
            {
                    .max_store_buf_size = 12 * 16,
                    .conv_frame_size = 12 * 16
            };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&handleCfg, &this->driverHandle));        // create the handle
    adc_continuous_config_t driverCfg = {                                               // and set the polling frequency
            .sample_freq_hz = SOC_ADC_SAMPLE_FREQ_THRES_LOW,                            // to the minimum possible ( 20khz )
            .conv_mode = ADC_CONV_SINGLE_UNIT_1,                                        // only use ADC1 for conversion (WIP)
            .format = ADC_DIGI_OUTPUT_FORMAT_TYPE1,                                     // set output to type 1 formatting
    };


    adc_digi_pattern_config_t adcPattern[SOC_ADC_PATT_LEN_MAX] = {{0}};            // <<< initialize the channels
    driverCfg.pattern_num = sizeof(channels) / sizeof(adc_channel_t);

    for (int i = 0; i < driverCfg.pattern_num; i++) {
        adcPattern[i].atten = ADC_ATTEN_DB_0;
        adcPattern[i].channel = channels[i] & 0x7;
        adcPattern[i].unit = ADC_UNIT_1;
        adcPattern[i].bit_width = ADC_BITWIDTH_12;
    }

    driverCfg.adc_pattern = adcPattern;                                             // >>> and, finally, create a driver


    ESP_ERROR_CHECK(adc_continuous_config(this->driverHandle, &driverCfg));
    adc_continuous_evt_cbs_t callbacks =
            {
                    .on_conv_done = dataReadyNotifier
            };

    bank1 = nullptr;
    bank2 = nullptr;

    xTaskCreate(&ioControllerTask,                                                  // create the task
                "ADCTask",                                                          // todo: reduce memory footprint
                8192 * 2,
                this,
                tskIDLE_PRIORITY,
                &this->TaskHandle);

    ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(this->driverHandle, &callbacks, this));
    ESP_ERROR_CHECK(adc_continuous_start(this->driverHandle));                     // and start the ADC

}

IOController::~IOController() {

}

void IOController::setPin(plcPin_t pin, bool dir) {
    // wip
}

// As per ESP32 datasheet, table 4.3:
// Logic level low : <= 0.825v
// Logic level high: >= 2.475v
// We make the assumption that any value under 2.3v is a logic level low
// 3.3v / 4096 = 0.000805 v / division
// => 2855 divisions for 2.3v


bool IOController::digiRead(plcPin_t pin) {
    return analogValues[pin.pinNum] > 2855;
}

uint16_t IOController::anaRead(plcPin_t pin) {                   // read the analog value
    return analogValues[pin.pinNum];
}

float IOController::anaReadVolts(plcPin_t pin, float vcc) {      // adjust for vcc
    return (float) analogValues[pin.pinNum] / 4096.0f * vcc;
}

void IOController::resetPins() {
    // wip
}

void IOController::digiWrite(plcPin_t pin, bool value) {

    switch (pin.port) {
        case 0:
        {
            bank1 ->setPinDir(pin.pinNum, M_PCA_OUTPUT);
            bank1 ->writePin(pin.pinNum, value);
            break;
        }
        case 1:
        {
            bank2 ->setPinDir(pin.pinNum, M_PCA_OUTPUT);
            bank2 ->writePin(pin.pinNum, value);
            break;
        }

    }


}

bool IOController::ready() {
    return (bank1 != nullptr) && (bank2 != nullptr);
}