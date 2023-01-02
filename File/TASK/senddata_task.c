#include "senddata_task.h"


 /** --------------------------------------------------------------------------
  * @brief  发送状态数据到上位机
			
  * @note	
 -------------------------------------------------------------------------- **/
void StateDataSend(void)
{	
	/** 状态更新 */
	StateDataSendBuff.State_Data1 = 1.23;
	StateDataSendBuff.State_Data10 = 4.56;

	/** DMA发送 */
	DMA_ClearITPendingBit(UART4_TX_STREAM, DMA_IT_TCIF4);								//没开中断的情况下标志位要手动清除，否则只发一次
	
	DMA_Cmd(UART4_TX_STREAM, DISABLE);				       								//设置当前计数值前先禁用DMA
	while (DMA_GetCmdStatus(UART4_TX_STREAM) != DISABLE){} 								//确保 DMA 可以被设置
	UART4_TX_STREAM->M0AR = (uint32_t)&StateDataSendBuff;								//设置当前待发数据基地址:Memory0 tARget
	UART4_TX_STREAM->NDTR = (uint32_t)STATE_SEND_DATA_LEN;			        			//设置当前待发的数据的数量:Number of Data units to be TRansferred
	DMA_Cmd(UART4_TX_STREAM, ENABLE);
}
