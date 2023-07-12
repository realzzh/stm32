#include "stm32f10x.h"

void Init_LED()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED_Turn()
{
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==1)
        GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    else
        GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
