#include "gimbal_protocol.h"
#include "global_declare.h"
#include "verify.h"
#include "string.h"


  /** --------------------------------------------------------------------------
  * @brief  解码云控板发送的机器人数据
			
  * @note	通信协议：首校验符(0x55和0x00)+通信数据(4x float + 1x u8)+CRC16校验码
 -------------------------------------------------------------------------- **/
void GimbalDataProtocol(void)
{
	if(	UA3RxDMAbuf[0]==0x55 &&																	// 帧头校验
		UA3RxDMAbuf[1]==0x00 &&																	
		Verify_CRC16_Check_Sum((u8*)UA3RxDMAbuf, UA3RxDMAbuf_LEN))								// 帧尾CRC16校验
	{
		memcpy(&GimbalDataBuff.Receive, (u8*)UA3RxDMAbuf, sizeof(GimbalDataBuff.Receive));		// 将串口DMA中数据赋给用户定义的结构体
		systemMonitor.USART3_valid_rx_cnt++;													// 对有效接收次数进行计数（计数周期为1s）
	}	
}

