//
// Created by shanai on 2024/1/16.
//

#include "../Inc/DS18B20.h"


#define DS18B20_GPIO_PORT GPIOB
#define DS18B20_GPIO_PIN GPIO_Pin_13


/**
 * 初始化 ds18b20
 */
void DS18B20_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);
    DS18B20_Reset();
}


void DS18B20_StartConversion(void) {
    DS18B20_Reset();
    ds18b20_write_byte(0xcc);   // 跳过ROM
    ds18b20_write_byte(0x44);   //温度转换
}

float DS18B20_ReadTemperature(void) {
    unsigned char TL,TH;
    short tem;
    DS18B20_StartConversion();
    delay_ms(700);
    DS18B20_Init();
    ds18b20_write_byte(0xCC);
    ds18b20_write_byte(0xBE);
    TL = ds18b20_read_byte();
    TH = ds18b20_read_byte();
    tem = TH;
    tem <<= 8;
    tem += TL;

    float v = 0;
    if ((tem&0xf800) == 0xf800)
    {
        tem = (~tem) + 1;
        v = tem * (-0.0625);
    } else {
        v = tem * (0.0625);
    }

    return v;
}

void DS18B20_Reset(void) {
    mode_output();
    GPIO_ResetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(600);
    GPIO_SetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
//    delay_us(30);
    mode_input();
    // 检测设备是否存在
    int time_out = 0;
    char *err = "not exist";
    while (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)) {
        delay_ms(10);
        time_out++;
        if (time_out >= 200) {
            OLED_ShowString(2,1,err);
            break;
        }
    };
    time_out = 0;
    while (!GPIO_ReadInputDataBit(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)) {
        delay_ms(10);
        time_out++;
        if (time_out >= 200) {
            OLED_ShowString(2,1,err);
            break;
        }
    };
}


void mode_output(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}

void mode_input(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}

void ds18b20_write_byte(unsigned char data) {
    unsigned char temp;
    mode_output();
    for (int i = 0; i < 8; ++i) {
        temp = data & 0x01;
        data >>= 1;
        if (temp) {
            ds18b20_write_one();
        } else {
            ds18b20_write_zero();
        }
    }
}

void ds18b20_write_one(void) {
    mode_output();
    GPIO_ResetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(3);
    GPIO_SetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(70);
}

void ds18b20_write_zero(void) {
    mode_output();
    GPIO_ResetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(70);
    GPIO_SetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(3);
}

unsigned char ds18b20_read_byte(void) {
    unsigned char i,j,data=0;
    for (int k = 0; k < 8; ++k) {
        j = ds18b20_read_bit();
        data = (j << 7) | (data >> 1);
    }
    return data;
}

unsigned char ds18b20_read_bit(void) {
    unsigned char data;
    mode_output();
    GPIO_ResetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    delay_us(2);
    GPIO_SetBits(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN);
    mode_input();
    delay_us(5);
    if (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN)) {
        data = 1;
    } else {
        data = 0;
    }
    delay_us(500);
    return data;
}




