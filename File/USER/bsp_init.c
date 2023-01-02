#include "bsp_init.h"
#include "delay.h"
#include "systick.h"
#include "usart.h"
#include "tim.h"
#include "led.h"


/** --------------------------------------------------------------------------
  * @brief  初始化函数
			
  * @note	对所有外设进行初始化
 -------------------------------------------------------------------------- **/
void BSP_Init(void)
{
	/** 设置中断组别 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);					// 16个抢断优先级，0个次优先级
	
	/** us计时器初始化 */
	TIM5_Configuration();

	/** LED初始化 */
	led_init();
	
	/** 串口初始化 */
	usart2_init();
	usart3_init();
	uart4_init();

}






