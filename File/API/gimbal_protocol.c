#include "gimbal_protocol.h"
#include "global_declare.h"
#include "verify.h"
#include "string.h"


  /** --------------------------------------------------------------------------
  * @brief  �����ƿذ巢�͵Ļ���������
			
  * @note	ͨ��Э�飺��У���(0x55��0x00)+ͨ������(4x float + 1x u8)+CRC16У����
 -------------------------------------------------------------------------- **/
void GimbalDataProtocol(void)
{
	if(	UA3RxDMAbuf[0]==0x55 &&																	// ֡ͷУ��
		UA3RxDMAbuf[1]==0x00 &&																	
		Verify_CRC16_Check_Sum((u8*)UA3RxDMAbuf, UA3RxDMAbuf_LEN))								// ֡βCRC16У��
	{
		memcpy(&GimbalDataBuff.Receive, (u8*)UA3RxDMAbuf, sizeof(GimbalDataBuff.Receive));		// ������DMA�����ݸ����û�����Ľṹ��
		systemMonitor.USART3_valid_rx_cnt++;													// ����Ч���մ������м�������������Ϊ1s��
	}	
}

