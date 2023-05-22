//
// Created by Alexandru Anastasiu on 5/21/23.
//

#include "eeprom.hpp"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int initEEPROM()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .sda_pullup_en=GPIO_PULLUP_DISABLE,
        .scl_pullup_en=GPIO_PULLUP_DISABLE,
    };
    conf.master.clk_speed = 400000;

    /*
     * gpio_reset_pin(GPIO_NUM_18);
    gpio_reset_pin(GPIO_NUM_19);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_18, true);
    gpio_set_level(GPIO_NUM_19, false);
     */

    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);


    return ESP_OK;
}

void writeByte(uint16_t addr, uint8_t byte)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x50 << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, (addr >> 8) & 0xFF, true);                   // High byte of address
    i2c_master_write_byte(cmd, addr & 0xFF, true);                          // Low byte of address
    i2c_master_write_byte(cmd, byte, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

uint8_t readByte(uint16_t addr)
{
    uint8_t data;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x50 << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, (addr >> 8) & 0xFF, true);                   // High byte of address
    i2c_master_write_byte(cmd, addr & 0xFF, true);                          // Low byte of address
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x50 << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &data, I2C_MASTER_ACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return data;
}