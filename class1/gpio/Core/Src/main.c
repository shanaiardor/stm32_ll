#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "OLED.h"
#include "DS18B20.h"

void float2Str(char* str,float value)
{
    int Head = (int)value;
    int Point = (int)((value - Head)*1000.0);
    sprintf(str, "temp:%d.%d", Head, Point);
}

int TRUE=1;
int main(void)
{
    delay_init();
//    GPIO_InitTypeDef  GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//
//
//    GPIO_Init(GPIOC,&GPIO_InitStructure);

    OLED_Init();		//OLED初始化
    DS18B20_Init();


    /*模块初始化*/
//    OLED_ShowChar(1, 1, 'A');				//1行1列显示字符A
//
//    OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
//
//    OLED_ShowNum(2, 1, 12345, 5);			//2行1列显示十进制数字12345，长度为5
//
//
//    OLED_ShowSignedNum(2, 7, -66, 2);		//2行7列显示有符号十进制数字-66，长度为2
//
//    OLED_ShowHexNum(3, 1, 0xAA55, 4);		//3行1列显示十六进制数字0xA5A5，长度为4
//
//    OLED_ShowBinNum(4, 1, 0xAA55, 16);		//4行1列显示二进制数字0xA5A5，长度为16
//    //C语言无法直接写出二进制数字，故需要用十六进制表示

    while (TRUE) {
        char charArray[50] = {};
        float temperature = DS18B20_ReadTemperature();
        float2Str(charArray,temperature);
        OLED_Clear();
        OLED_ShowString(1, 1, charArray);
        delay_ms(800);
    }
    return 0;
}


