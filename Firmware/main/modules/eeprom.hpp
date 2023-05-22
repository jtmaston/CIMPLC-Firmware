//
// Created by Alexandru Anastasiu on 5/21/23.
//

#ifndef FIRMWARE_EEPROM_HPP
#define FIRMWARE_EEPROM_HPP

#include <esp_attr.h>
#include <rtc.h>


int initEEPROM();
void writeByte(uint16_t addr, uint8_t byte);
uint8_t readByte(uint16_t addr);

#endif //FIRMWARE_EEPROM_HPP
