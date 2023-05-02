//
// Created by Alexandru Anastasiu on 2/9/23.
//
#include <init/serialInit.hpp>


const uart_config_t loraSerialParameters = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122U,
        .source_clk = UART_SCLK_DEFAULT
};

void initializeSerialPorts()
{
#if CONFIG_UART_ISR_IN_IRAM
    int interrAllocFlags = ESP_INTR_FLAG_IRAM;
#else
    int interrAllocFlags = 0;
#endif

    ESP_ERROR_CHECK(uart_driver_install(LORA_SERIAL, 1024 * 2,
                                        0, 0, nullptr,
                                        interrAllocFlags ));

    ESP_ERROR_CHECK(uart_param_config(LORA_SERIAL, &loraSerialParameters));
    ESP_ERROR_CHECK(uart_set_pin(LORA_SERIAL, GPIO_NUM_1, GPIO_NUM_3,
                                 GPIO_NUM_NC, GPIO_NUM_NC));

    ESP_ERROR_CHECK(uart_driver_install(GPS_SERIAL, 1024,
                                        0, 0, nullptr,
                                        interrAllocFlags ));
    ESP_ERROR_CHECK(uart_param_config(GPS_SERIAL, &loraSerialParameters));
    ESP_ERROR_CHECK(uart_set_pin(GPS_SERIAL, GPIO_NUM_17, GPIO_NUM_16,
                                 GPIO_NUM_NC, GPIO_NUM_NC));
}