#include "led_task.h"


 /** --------------------------------------------------------------------------
  * @brief  LEDָʾ����ʾ��������״̬
			
  * @note	
 -------------------------------------------------------------------------- **/
void LEDStateChange(void)
{
	if(stError.DNGimbalState)		// �ƿ�ͨ�ŷ����������ȵ�
	{
		LED_ORANGE_TOGGLE();
	}
	if(stError.RSState)				// ����ϵͳ�������ݷ�������������
	{
		LED_BLUE_TOGGLE();
	}
	if(stError.DNComputerState)		// ����ͨ�Ŵ������۵�
	{
		LED_PINK_TOGGLE();
	}
	
	LED_GREEN_TOGGLE();				// ���������������̵�
}
