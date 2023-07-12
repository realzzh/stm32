#include "stm32f10x.h"

void InitLed()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef IO_A;
    IO_A.GPIO_Mode=GPIO_Mode_Out_PP;
    IO_A.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;
    IO_A.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&IO_A);
    GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

void LED1_Open()
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_Close()
{
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED2_Open()
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_Close()
{
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED1_Turn()
{
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==1)
        GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    else
        GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED2_Turn()
{
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==1)
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    else
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
