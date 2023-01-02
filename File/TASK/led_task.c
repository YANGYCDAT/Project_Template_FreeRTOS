#include "led_task.h"


 /** --------------------------------------------------------------------------
  * @brief  LED指示灯显示程序运行状态
			
  * @note	
 -------------------------------------------------------------------------- **/
void LEDStateChange(void)
{
	if(stError.DNGimbalState)		// 云控通信发生错误闪橙灯
	{
		LED_ORANGE_TOGGLE();
	}
	if(stError.RSState)				// 裁判系统接收数据发生错误闪蓝灯
	{
		LED_BLUE_TOGGLE();
	}
	if(stError.DNComputerState)		// 电脑通信错误闪粉灯
	{
		LED_PINK_TOGGLE();
	}
	
	LED_GREEN_TOGGLE();				// 程序正常运行闪绿灯
}
