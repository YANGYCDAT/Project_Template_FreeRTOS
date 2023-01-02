#include "systemmonitor_task.h"


 /** --------------------------------------------------------------------------
  * @brief  系统任务以及中断帧率检测
			
  * @note	
 -------------------------------------------------------------------------- **/
void SystemMonitorDetect(void)
{	
/*帧率异常检测*/
	if(systemMonitor.USART2_rx_fps < 500)	{	stError.DNGimbalState = TRUE;}								// 下云控通信帧率异常检测
	else									{	stError.DNGimbalState = FALSE;}

}
