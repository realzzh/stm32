#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Timer.h"
#include "LCD1602.h"
// #include "Key.h"
#include "KeyBoard.h"

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
#define SERVO_STEP_SIZE 1
#define PWM_MIN_DUTY_CYCLE 1000
#define PWM_MAX_DUTY_CYCLE 2000

void UpdateOLED(int16_t angle);

int speed=0;					//目标速度，初始化为0
int target_angle = 0;			//目标角度,初始化为0			

uint16_t Num;
 
 // 变量定义
uint8_t angle = 0;
uint8_t Key_Num = 0;

int main(void)
{
	
    int current_angle = 0;			//实际角度
    int16_t error = 0;					//误差
	
	LCD_INIT();
	Servo_Init();		//舵机初始化
	Timer_Init();		//TIM3定时器初始化
//	Key_Init();
	KeyBoard_Init();
	
	LCD_WRITE_StrDATA("Ang:0",0,0);		//OLED显示字符串
	LCD_WRITE_StrDATA("Speed:0",1,0);

	
	Servo_SetAngle(0);
	Delay_ms(500);
	
	while (1)								//主循环
	{
		KeyDriver();
		if(Key_Num == 3){
			Servo_SetAngle(SERVO_MIN_ANGLE);
			Key_Num = 0;
			target_angle=0;
			Num=0;
			LCD_WRITE_StrDATA("0  ",0,4);
			LCD_WRITE_StrDATA("0  ",1,6);
			LCD_WRITE_StrDATA("   ",0,13);
		}
		if(Key_Num == 1)
		{
			LCD_WRITE_StrDATA("   ", 0, 4);
			//舵机旋转
			for (current_angle = SERVO_MIN_ANGLE; current_angle <= SERVO_MAX_ANGLE; current_angle += SERVO_STEP_SIZE)
			{	  
				Num=current_angle;
				error = current_angle - target_angle;
			
			if (error >= 0)
			{
				Servo_SetAngle(current_angle - SERVO_STEP_SIZE);			//控制舵机旋转到指定的角度
			}
			else if (error < 0)
			{
				Servo_SetAngle(current_angle + SERVO_STEP_SIZE);
			}		
		
			if(current_angle==target_angle)         //终止条件
			{
				Key_Num = 2;
				break;
			}  
			Delay_ms(1000 / speed); 					// 控制舵机旋转速度
			}
		}
    }
}

// 更新OLED显示
void UpdateOLED(int16_t angle)
{
    LCD_WRITE_NUM(angle,0,4);				//OLED显示
}

//TIM3定时中断
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		UpdateOLED(Num);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

/*TIM4扫描按键*/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		KeyScan();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
