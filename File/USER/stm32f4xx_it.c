#include "stm32f4xx_it.h"
#include "global_declare.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "global_declare.h"
#include "os_types.h"
#include "gimbal_protocol.h"

extern void xPortSysTickHandler(void);


/** --------------------------------------------------------------------------
  * @brief  系统时钟中断
			
  * @note	进行FreeRTOS系统任务调度处理，1ms进入一次
 -------------------------------------------------------------------------- **/
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)			// 系统已经运行
    {
        xPortSysTickHandler();										// 系统任务调度处理（判断任务切换需求并处理）
    }

	if(systemMonitor.SysTickTime % 1000 == 0)						// 用1s内的次数计算帧率
	{
		/** Main Task Monitor */
		DETECT_MONITOR(SystemMonitorTask);
		DETECT_MONITOR(StateDataSendTask);
		DETECT_MONITOR(CommunicateTask);
		DETECT_MONITOR(LEDTask);
		
		/** IT Monitor */
		DETECT_MONITOR(USART2_rx);
		DETECT_MONITOR(USART3_rx);
		DETECT_MONITOR(USART3_valid_rx);
		DETECT_MONITOR(UART4_rx);

	}
		
	systemMonitor.SysTickTime++;

}



/** --------------------------------------------------------------------------
  * @brief  串口2中断服务函数
  
  * @retval None
  
  * @param	None
			
  * @note	
 -------------------------------------------------------------------------- **/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
  {
		USART2->SR;
		USART2->DR;                   

		/* 协议解析*/
	  
		/***********/
	  
		systemMonitor.USART2_rx_cnt++;																	// 对接收次数进行计数（计数周期为1s）
	}	
}


/** --------------------------------------------------------------------------
  * @brief  串口3中断服务函数
  
  * @retval None
  
  * @param	None
			
  * @note	
 -------------------------------------------------------------------------- **/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_IDLE) == SET)
	{
		USART3->SR;
		USART3->DR;
		
		/* 协议解析*/
		GimbalDataProtocol();
		/***********/

		DMA_Cmd(USART3_RX_STREAM, DISABLE);													// DMA清空为下一次接收做准备
		USART3_RX_STREAM->NDTR = UA3RxDMAbuf_LEN;
		DMA_Cmd(USART3_RX_STREAM, ENABLE);
		
		systemMonitor.USART3_rx_cnt++;														// 对接收次数进行计数（1s内）
	}
}




/** --------------------------------------------------------------------------
  * @brief  串口4中断服务函数
  
  * @retval None
  
  * @param	None
			
  * @note	
 -------------------------------------------------------------------------- **/
void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4, USART_IT_IDLE) == SET)
	{
		UART4->SR;
		UART4->DR;
		
		/* 协议解析*/
		/***********/

		DMA_Cmd(UART4_RX_STREAM, DISABLE);
		UART4_RX_STREAM->NDTR = UA4RxDMAbuf_LEN;											// DMA清空为下一次接收做准备
		TestBox.TestUValue1 = UART4_RX_STREAM->CR;
		DMA_Cmd(UART4_RX_STREAM, ENABLE);
		
		systemMonitor.UART4_rx_cnt++;														// 对接收次数进行计数（1s内）

	}
}
