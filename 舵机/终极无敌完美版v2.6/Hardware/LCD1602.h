#ifndef LCD1602_H
#define LCD1602_H

#include "stm32f10x_gpio.h"

/***********************************引脚定义********************************************/
#define BUSY 0x80		//忙标志
#define RS GPIO_Pin_5	//设置PB5为RS
#define RW GPIO_Pin_6	//PB6为RW
#define EN GPIO_Pin_7	//PB7为EN使能
//PA0 ~ PA7对应D0 ~D7
/***********************************引脚定义********************************************/

/***********************************函数定义********************************************/
void ReadBusy(void);
void LCD_WRITE_CMD( unsigned char CMD );
void LCD_WRITE_StrDATA( char *StrData, unsigned char row, unsigned char col );
void LCD_WRITE_NUM(uint32_t num,unsigned char row,unsigned char col);
void LCD_WRITE_ByteDATA( unsigned char ByteData );
void LCD_INIT(void);
void GPIO_INIT(void);
void WUserImg(unsigned char pos,unsigned char *ImgInfo);
unsigned char NumtoStr(char *str,uint32_t num);
/***********************************函数定义********************************************/
#endif

