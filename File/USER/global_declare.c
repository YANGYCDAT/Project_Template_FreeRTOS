#include "global_declare.h"



/** 系统状态 */
ST_FLAG 	stFlag = {FALSE};										// 全局标志位
ST_ERROR 	stError = {FALSE};										// 模块异常标志位
SYSTEM_MONITOR systemMonitor 		= {0};							// 系统监视器

/** 测试数据包 */
TESTBOX TestBox;

/** DMA接收缓存 */
u8 UA3RxDMAbuf[UA3RxDMAbuf_LEN] = {0};								// 串口3接收缓存
u8 UA4RxDMAbuf[UA4RxDMAbuf_LEN + 10] = {0};							// 串口3接收缓存

ST_UART_DATA_VOFA StateDataSendBuff = {.Tail1 = 0x00, .Tail2 = 0x00, .Tail3 = 0x80, .Tail4 = 0x7F};		// 上位机发送数据包
ST_IMU GimbalDataBuff = {.Send.head[0] = 0x55, .Send.head[1] = 0x00};									// 云台通信数据包
