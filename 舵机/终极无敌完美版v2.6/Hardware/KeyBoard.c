#include "stm32f10x.h"
#include "KeyBoard.h"
#include "LCD1602.h"

void KeyAction(unsigned char);
void NumAction(unsigned char num);
void enter();
void esc();

unsigned char KeyMap[4][4]={
    '1','2','3',0x26,
    '4','5','6',0x25,
    '7','8','9',0x28,
    '0',0x1B,0x0D,0x27
};

unsigned char now[4][4]={
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1
};

/*和键盘有关的变量*/
unsigned char step=0;		//选择输入角度或者速度
long Number1=0;				//输入角度
long Number2=0;				//输入速度

extern int target_angle;
extern int speed;
extern uint8_t Key_Num;

void KeyBoard_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef PA,PB;
    PA.GPIO_Mode=GPIO_Mode_IPU;
    PA.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    PA.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&PA);

    PB.GPIO_Mode=GPIO_Mode_Out_PP;
    PB.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    PB.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&PB);

    GPIO_Write(GPIOB,((GPIOB->ODR & 0x0fff) | 0xf000));
}

void KeyDriver()
{
    unsigned char i,j;
    static unsigned char before[4][4]=
    {
        1,1,1,1,
        1,1,1,1,
        1,1,1,1,
        1,1,1,1
    };
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(now[i][j]!=before[i][j])
            {
                if(before[i][j])               
                    KeyAction(KeyMap[i][j]);                
                before[i][j]=now[i][j];
            }
        }
    }
}

void KeyScan()
{
    static unsigned char keyout=0;
    unsigned char i;
    static unsigned char keybuf[4][4]={
        0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF
    };
    keybuf[keyout][0]=(keybuf[keyout][0]<<1) | GPIO_ReadInputDataBit(GPIOA,KEY_OUT1);
    keybuf[keyout][1]=(keybuf[keyout][1]<<1) | GPIO_ReadInputDataBit(GPIOA,KEY_OUT2);
    keybuf[keyout][2]=(keybuf[keyout][2]<<1) | GPIO_ReadInputDataBit(GPIOA,KEY_OUT3);
    keybuf[keyout][3]=(keybuf[keyout][3]<<1) | GPIO_ReadInputDataBit(GPIOA,KEY_OUT4);
    for(i=0;i<4;i++)
    {
        if((keybuf[keyout][i] & 0x0F)==0x0F)
            now[keyout][i]=1;
        if((keybuf[keyout][i] & 0x0F)==0x00)
            now[keyout][i]=0;
    }
    keyout++;
    keyout &= 0x03;
    switch(keyout)
    {
        case 0: GPIO_SetBits(GPIOB,KEY_IN4); GPIO_ResetBits(GPIOB,KEY_IN1); break;
        case 1: GPIO_SetBits(GPIOB,KEY_IN1); GPIO_ResetBits(GPIOB,KEY_IN2); break;
        case 2: GPIO_SetBits(GPIOB,KEY_IN2); GPIO_ResetBits(GPIOB,KEY_IN3); break;
        case 3: GPIO_SetBits(GPIOB,KEY_IN3); GPIO_ResetBits(GPIOB,KEY_IN4); break;
    }
}

void KeyAction(unsigned char keycode)
{
	if(keycode>='0' && keycode<='9')
    {
        NumAction(keycode - '0'); 
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
        enter();
    }
    else if(keycode==0x0D)
    {
        esc();
    }
    else if(keycode==0x27)
    {
        Key_Num++;
    }
}

void NumAction(unsigned char num)
{
    char str[12];
    unsigned char len;
    if(step==0)
    {
        Number1=Number1*10+num;
        len=NumtoStr(str,Number1);
        LCD_WRITE_StrDATA(str,0,13);		//显示输入角度
    }
    else if(step==1)
    {
        Number2=Number2*10+num;
        len=NumtoStr(str,Number2);
        LCD_WRITE_StrDATA(str,1,13);		//显示输入速度
    }
}

void enter()
{
    char str[12];
    if(step==0)
    {
        target_angle=Number1;
        Number1=0;
        step++;
    }
    else if(step==1)
    {        
        speed=Number2;
        Number2=0;
        NumtoStr(str,speed);
        LCD_WRITE_StrDATA(str,1,6);
        LCD_WRITE_StrDATA("   ",1,13);
        Key_Num=1;
        step=0;
    }
    // else if(step==2)
    // {    
    //     target_angle=Number1;
    //     Number1=0;
    //     step=0;
    // }
}

void esc()
{
    if(step==0)
    {
        Number1=0;
        LCD_WRITE_StrDATA("   ",0,13);
    }
    else if(step==1)
    {
        Number2=0;
        LCD_WRITE_StrDATA("   ",1,13);
    }
    // else if(step==2)
    // {
    //     Number1=0;
    //     LCD_WRITE_StrDATA("   ",0,4);
    //     speed=0;
    //     Number2=0;
    //     LCD_WRITE_StrDATA("     ",1,6);

    // }
}