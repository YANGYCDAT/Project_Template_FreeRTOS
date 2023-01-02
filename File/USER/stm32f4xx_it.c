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
  * @brief  ϵͳʱ���ж�
			
  * @note	����FreeRTOSϵͳ������ȴ���1ms����һ��
 -------------------------------------------------------------------------- **/
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)			// ϵͳ�Ѿ�����
    {
        xPortSysTickHandler();										// ϵͳ������ȴ����ж������л����󲢴���
    }

	if(systemMonitor.SysTickTime % 1000 == 0)						// ��1s�ڵĴ�������֡��
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
  * @brief  ����2�жϷ�����
  
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

		/* Э�����*/
	  
		/***********/
	  
		systemMonitor.USART2_rx_cnt++;																	// �Խ��մ������м�������������Ϊ1s��
	}	
}


/** --------------------------------------------------------------------------
  * @brief  ����3�жϷ�����
  
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
		
		/* Э�����*/
		GimbalDataProtocol();
		/***********/

		DMA_Cmd(USART3_RX_STREAM, DISABLE);													// DMA���Ϊ��һ�ν�����׼��
		USART3_RX_STREAM->NDTR = UA3RxDMAbuf_LEN;
		DMA_Cmd(USART3_RX_STREAM, ENABLE);
		
		systemMonitor.USART3_rx_cnt++;														// �Խ��մ������м�����1s�ڣ�
	}
}




/** --------------------------------------------------------------------------
  * @brief  ����4�жϷ�����
  
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
		
		/* Э�����*/
		/***********/

		DMA_Cmd(UART4_RX_STREAM, DISABLE);
		UART4_RX_STREAM->NDTR = UA4RxDMAbuf_LEN;											// DMA���Ϊ��һ�ν�����׼��
		TestBox.TestUValue1 = UART4_RX_STREAM->CR;
		DMA_Cmd(UART4_RX_STREAM, ENABLE);
		
		systemMonitor.UART4_rx_cnt++;														// �Խ��մ������м�����1s�ڣ�

	}
}
