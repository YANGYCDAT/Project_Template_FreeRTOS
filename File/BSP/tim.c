#include "tim.h"

#define TIM5_PRE 	84-1
#define TIM5_PER	0xFFFFFFFFUL

/** --------------------------------------------------------------------------
  * @brief  TIM5��ʼ��Ϊ��ʱ��
  
  * @retval None
  
  * @param	None
			
  * @note	APB1=84MHz
			����Ϊ1us����һ��
 -------------------------------------------------------------------------- **/
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler		= TIM5_PRE;
	TIM_TimeBaseStructure.TIM_Period		= TIM5_PER;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;				// ����Ϊ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM5, ENABLE);
}

