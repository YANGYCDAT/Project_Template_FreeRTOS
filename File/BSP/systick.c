#include "systick.h"



/** --------------------------------------------------------------------------
  * @brief  设置系统时钟的中断时间间隔
			
  * @note	将系统时钟的中断时间间隔设置为1ms
			与 SysTick_Handler 系统时钟中断服务函数结合使用
			对程序运行时间进行计时（准确计时）
 -------------------------------------------------------------------------- **/
void SysTick_init(void)
{
    //SYSTICK分频	--	1ms的系统时钟中断
    //SystemCoreClock / 1000     1ms
    //SystemCoreClock / 100000   10us
    //SystemCoreClock / 1000000  1us
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		//错误捕获
		while(1);
	}
}
