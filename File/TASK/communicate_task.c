#include "communicate_task.h"


 /** --------------------------------------------------------------------------
  * @brief  向云台发送数据
			
  * @note	与云台进行通信，带CRC16校验
 -------------------------------------------------------------------------- **/
void GimbalDataSend(void)
{
	GimbalDataBuff.Send.Send_Data1			= 1;
	GimbalDataBuff.Send.Send_Data2			= 2;
	GimbalDataBuff.Send.Send_Data3			= 3;
	GimbalDataBuff.Send.Flag_1				= stFlag.ResetFlag;
	GimbalDataBuff.Send.Flag_1				= stFlag.InitFlag;
	Append_CRC16_Check_Sum(&GimbalDataBuff.Send.head[0], GimbalTxDMABuffLEN);
	
	DMA_ClearITPendingBit(USART3_TX_STREAM, DMA_IT_TCIF3);
	
	DMA_Cmd(USART3_TX_STREAM, DISABLE);
	USART3_TX_STREAM->M0AR = (u32)&GimbalDataBuff.Send;
	USART3_TX_STREAM->NDTR = (u32)GimbalTxDMABuffLEN;
	DMA_Cmd(USART3_TX_STREAM, ENABLE);
}
