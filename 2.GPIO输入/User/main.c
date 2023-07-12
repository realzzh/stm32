#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "LED.h"

int main()
{
	uint8_t Key=0;
	InitKey();
	InitLed();
	
	while(1)
	{
		Key=KeyNum();
		if(Key==1)
			LED1_Turn();
		else if(Key==2)
			LED2_Turn();
	}
}
