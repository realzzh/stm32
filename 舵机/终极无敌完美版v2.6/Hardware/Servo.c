#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)					//舵机初始化
{
	PWM_Init();							//PWM初始化
}

void Servo_SetAngle(float Angle)		//舵机设置角度
{															//0————————————————500
	PWM_SetCompare2(Angle / 180 * 2000 + 500);				//180——————————————2500
}
