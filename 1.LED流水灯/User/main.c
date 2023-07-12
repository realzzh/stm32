#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_AStruct;
	GPIO_AStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_AStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_AStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_AStruct);
	
	while(1)
	{
		GPIO_Write(GPIOA,0x0001);
		Delay_ms(500);
		GPIO_Write(GPIOA,0x0000);
		Delay_ms(200);
		
	}
}
