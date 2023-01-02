#include "senddata_task.h"


 /** --------------------------------------------------------------------------
  * @brief  ����״̬���ݵ���λ��
			
  * @note	
 -------------------------------------------------------------------------- **/
void StateDataSend(void)
{	
	/** ״̬���� */
	StateDataSendBuff.State_Data1 = 1.23;
	StateDataSendBuff.State_Data10 = 4.56;

	/** DMA���� */
	DMA_ClearITPendingBit(UART4_TX_STREAM, DMA_IT_TCIF4);								//û���жϵ�����±�־λҪ�ֶ����������ֻ��һ��
	
	DMA_Cmd(UART4_TX_STREAM, DISABLE);				       								//���õ�ǰ����ֵǰ�Ƚ���DMA
	while (DMA_GetCmdStatus(UART4_TX_STREAM) != DISABLE){} 								//ȷ�� DMA ���Ա�����
	UART4_TX_STREAM->M0AR = (uint32_t)&StateDataSendBuff;								//���õ�ǰ�������ݻ���ַ:Memory0 tARget
	UART4_TX_STREAM->NDTR = (uint32_t)STATE_SEND_DATA_LEN;			        			//���õ�ǰ���������ݵ�����:Number of Data units to be TRansferred
	DMA_Cmd(UART4_TX_STREAM, ENABLE);
}
