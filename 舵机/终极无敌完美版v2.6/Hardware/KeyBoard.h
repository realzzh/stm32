#ifndef __KeyBoard_H
#define __KeyBoard_H

#include "stm32f10x_gpio.h"

#define KEY_IN1 GPIO_Pin_12
#define KEY_IN2 GPIO_Pin_13
#define KEY_IN3 GPIO_Pin_14
#define KEY_IN4 GPIO_Pin_15
//PB12~15
#define KEY_OUT1 GPIO_Pin_8
#define KEY_OUT2 GPIO_Pin_9
#define KEY_OUT3 GPIO_Pin_10
#define KEY_OUT4 GPIO_Pin_11
//PA8~11

void KeyBoard_Init();
void KeyDriver();
void KeyScan();
// unsigned char NumtoStr(char *str,long num);


#endif