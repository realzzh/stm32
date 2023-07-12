#include "stm32f10x.h"
#include "Timer.h"

void Timer_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef Timstruct;
    Timstruct.TIM_ClockDivision=TIM_CKD_DIV1;
    Timstruct.TIM_CounterMode=TIM_CounterMode_Up;
    Timstruct.TIM_Period=10000-1;
    Timstruct.TIM_Prescaler=7200-1;
    Timstruct.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&Timstruct);

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVICstruct;
    NVICstruct.NVIC_IRQChannel=TIM2_IRQn;
    NVICstruct.NVIC_IRQChannelCmd=ENABLE;
    NVICstruct.NVIC_IRQChannelPreemptionPriority=2;
    NVICstruct.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVICstruct);

    TIM_Cmd(TIM2,ENABLE);
}

