#include "wwdg.h"


u8 WWDG_Counter = 0x6F;//低6位是0x2F=101111(2)=47(10)





/** --------------------------------------------------------------------------
  * @brief  窗口看门狗初始化
  
  * @retval None
  
  * @param	None
			
  * @note	计数器值大于上窗口值就被刷新 或 0x40跳变为0x3F时复位
			下窗口值时固定的，为0x40，而上窗口值可以设置，
			当前值为0x40时唤醒中断服务函数
			要在计数值满足0x40=下窗口<计数值<=上窗口<=0x7F时进行喂狗刷新计数值，
			优先级0-0
 -------------------------------------------------------------------------- **/
void WWDG_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    //定时时间为4096*2^WWDG_Prescaler*(T[5:0]+1)/42M=4096*2^2*(0x2F + 1)/42M=18.72ms
    WWDG_SetPrescaler(WWDG_Prescaler_2);    											// 设置预分频系数，
    WWDG_SetWindowValue(0x7F);              											// 设置上窗口值，<=0x7F,上
    WWDG_Enable(WWDG_Counter);              											// 使能窗口看门狗,值在0x40-0x7F之间

    NVIC_InitStructure.NVIC_IRQChannel 						= WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
    NVIC_Init(&NVIC_InitStructure);

    WWDG_ClearFlag();
    WWDG_EnableIT();																	// 使能中断
}

