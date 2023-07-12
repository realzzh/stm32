#include"stm32f10x.h"
#include"Delay.h"

void InitKey()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef IO_B;
    IO_B.GPIO_Mode=GPIO_Mode_IPU;
    IO_B.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_11;
    IO_B.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOB,&IO_B);
}

uint8_t KeyNum()
{
    uint8_t KeyNum=0;
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
        Delay_ms(20);
        KeyNum=1;
    }
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
        Delay_ms(20);
        KeyNum=2;
    }
    return KeyNum;
}
