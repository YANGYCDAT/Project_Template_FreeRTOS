#include "systemmonitor_task.h"


 /** --------------------------------------------------------------------------
  * @brief  ϵͳ�����Լ��ж�֡�ʼ��
			
  * @note	
 -------------------------------------------------------------------------- **/
void SystemMonitorDetect(void)
{	
/*֡���쳣���*/
	if(systemMonitor.USART2_rx_fps < 500)	{	stError.DNGimbalState = TRUE;}								// ���ƿ�ͨ��֡���쳣���
	else									{	stError.DNGimbalState = FALSE;}

}
