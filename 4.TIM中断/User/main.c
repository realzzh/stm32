#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "KeyBoard.h"

void KeyAction(unsigned char);
void NumKeyAction(unsigned char num);
unsigned char NumtoStr(unsigned char *str,long num);

unsigned char step=0;
long Number1=0;
long Number2=0;

int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1, 3, "HelloWorld!");
	
	while (1)
	{
		KeyDriver();
	}
}

void KeyAction(unsigned char keycode)
{
	if(keycode>='0' && keycode<='9')
    {
        NumKeyAction(keycode - '0'); 
    }
    else if(keycode==0x26)
    {
        step=0;
    }
    else if(keycode==0x25)
    {
        step=1;
    }
    else if(keycode==0x1B)
    {
//        enter();
    }
    else if(keycode==0x0D)
    {
//        esc();
    }
}

void NumKeyAction(unsigned char num)
{
    unsigned char str[12];
    unsigned char len;
    if(step==0)
    {
        Number1=Number1*10+num;
        len=NumtoStr(str,Number1);
        OLED_ShowString(1,1,str);
    }
    else if(step==1)
    {
        Number2=Number2*10+num;
        len=NumtoStr(str,Number2);
//        LcdShowStr(16-len,1,str);
    }

}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
        KeyScan();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
/*将数字转换成字符串*/
unsigned char NumtoStr(unsigned char *str,long num)
{
    unsigned char i=0;
    unsigned char len=0;
    unsigned char strbuf[12];
    if(num<0)
    {
        num = -num;
        *str++='-';
        len++;
    }
    do 
    {
        strbuf[i]=num % 10;
        num /= 10;
        i++;
    }while(num>0);
    len += i;
    while(i-- > 0)
    {
        *str++ = strbuf[i]+'0';
    }
    *str='\0';
    return len;
}
