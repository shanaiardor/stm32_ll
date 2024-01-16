//
// Created by shanai on 2024/1/16.
//

#ifndef TEMPLATEF103_DS18B20_H
#define TEMPLATEF103_DS18B20_H

#include <stm32f10x.h>
#include <delay.h>
#include "OLED.h"

void mode_output(void);
void mode_input(void);

void DS18B20_Init(void);
void DS18B20_Reset(void);
//void ds18b20_start(void);

void ds18b20_write_byte(unsigned char data);
unsigned char ds18b20_read_byte(void);
void ds18b20_write_one(void);
void ds18b20_write_zero(void);
unsigned char ds18b20_read_bit(void);

void DS18B20_StartConversion(void);
float DS18B20_ReadTemperature(void);

#endif //TEMPLATEF103_DS18B20_H
