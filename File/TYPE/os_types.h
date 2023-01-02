#ifndef OS_TYPES_H
#define OS_TYPES_H

#include "stm32f4xx.h"
#include "global_types.h"

/** 系统监视 */
#define DECLARE_MONITOR(name) 		u16 name##_cnt; u16 name##_fps
#define DETECT_MONITOR(name)    	systemMonitor.name##_fps = systemMonitor.name##_cnt; systemMonitor.name##_cnt = 0
#define DECLARE_EXECUTE_TIME(name)	u32 name##_ExecuteTime

/** 任务帧率统计结构体 */
typedef struct
{	
	DECLARE_MONITOR(System);
	
	/** Main Task Monitor */
	DECLARE_MONITOR(SystemMonitorTask);
	DECLARE_MONITOR(StateDataSendTask);
	DECLARE_MONITOR(CommunicateTask);
	DECLARE_MONITOR(LEDTask);


	/** IT Monitor */
	DECLARE_MONITOR(USART2_rx);
	DECLARE_MONITOR(USART3_rx);
	DECLARE_MONITOR(USART3_valid_rx);
	DECLARE_MONITOR(UART4_rx);

	/** Task Carry Time **/
	DECLARE_EXECUTE_TIME(SystemMonitorTask);
	DECLARE_EXECUTE_TIME(StateDataSendTask);
	DECLARE_EXECUTE_TIME(CommunicateTask);
	DECLARE_EXECUTE_TIME(LEDTask);

	/* SysTickTime */
	u32 SysTickTime;
} SYSTEM_MONITOR;

#endif
