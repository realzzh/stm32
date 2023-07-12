#include "stm32f10x.h"
#include "KeyBoard.h"

extern void KeyAction(unsigned char);

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

void KeyBoard_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef PA,PB;
    PA.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    PA.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    PA.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&PA);

    PB.GPIO_Mode=GPIO_Mode_Out_PP;
    PB.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    PB.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&PB);

    GPIO_Write(GPIOA,0x00);
    GPIO_Write(GPIOB,0x00);
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
