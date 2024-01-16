#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "string.h"


int TRUE=1;
int main(void)
{
    delay_init();
//    uart_init(115200);
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


    GPIO_InitTypeDef  GPIO_InitStructure_B;
    GPIO_InitStructure_B.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure_B.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_B.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC,&GPIO_InitStructure);
    GPIO_Init(GPIOB,&GPIO_InitStructure_B);

    while (TRUE) {
        GPIO_SetBits(GPIOC,GPIO_Pin_15);
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        delay_ms(500);
        GPIO_ResetBits(GPIOC,GPIO_Pin_15);
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        delay_ms(500);
//        USART_SEND(USART1,"Hello World!\n");
    }
    return 0;
}
