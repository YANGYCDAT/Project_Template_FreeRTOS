#include "tim.h"

#define TIM5_PRE 	84-1
#define TIM5_PER	0xFFFFFFFFUL

/** --------------------------------------------------------------------------
  * @brief  TIM5初始化为计时器
  
  * @retval None
  
  * @param	None
			
  * @note	APB1=84MHz
			配置为1us计数一次
 -------------------------------------------------------------------------- **/
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler		= TIM5_PRE;
	TIM_TimeBaseStructure.TIM_Period		= TIM5_PER;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;				// 配置为向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM5, ENABLE);
}

