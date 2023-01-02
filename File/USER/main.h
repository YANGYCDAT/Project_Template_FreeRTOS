#ifndef MAIN_H
#define MAIN_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp_init.h"
#include "global_declare.h"
#include "systemmonitor_task.h"
#include "led_task.h"
#include "senddata_task.h"
#include "communicate_task.h"

/**********************************************************************任务分配************************************************************/
						

#define StateDataSend_TASK_PRIO 			1					
#define StateDataSend_STK_SIZE				200				
#define StateDataSend_TASK_CYCLE			10										
TaskHandle_t								StateDataSendTask_Handler;	
void 	StateDataSend_Task(void);									

#define Communicate_TASK_PRIO 				2					
#define Communicate_STK_SIZE				200				
#define Communicate_TASK_CYCLE				1										
TaskHandle_t								CommunicateTask_Handler;	
void 	Communicate_Task(void);						

#define Monitor_TASK_PRIO 					3					
#define Monitor_STK_SIZE					200				
#define Monitor_TASK_CYCLE					1000										
TaskHandle_t								MonitorTask_Handler;	
void 	Monitor_Task(void);						

#define LED_TASK_PRIO 						4									/* 任务优先级 	*/
#define LED_STK_SIZE						200									/* 任务堆栈大小 */
#define LED_TASK_CYCLE						500									/* 任务执行周期(ms) */
TaskHandle_t								LEDTask_Handler;					/* 任务句柄 	*/
void 	LED_Task(void);															/* 任务函数		*/

/**********************************************************************消息队列句柄************************************************************/
QueueHandle_t Test_Queue;
#define	TESET_QUEUE_SIZE 					16
#define	TESET_QUEUE_ITEM_SIZE 				4




extern u32 III;
extern QueueHandle_t Test_Queue;
extern TaskHandle_t	MonitorTask_Handler;				
extern TaskHandle_t	ModeChooseTask_Handler;				
extern TaskHandle_t	ShootTask_Handler;				
extern TaskHandle_t	ChassisTask_Handler;				
extern TaskHandle_t	GimbalTask_Handler;				
extern TaskHandle_t	MotorDataSendTask_Handler;				
extern TaskHandle_t	GimbalDataSendTask_Handler;				
extern TaskHandle_t	VisionDataSendTask_Handler;				
extern TaskHandle_t	StateDataSendTask_Handler;				
extern TaskHandle_t	LEDTask_Handler;	


void Task_Create(void);										


#endif
