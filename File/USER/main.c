#include "main.h"

/***********************************************************************主函数************************************************************/

int main(void)
{
	/* 初始化 */
	BSP_Init();

	/* 创建任务 */
	Task_Create();
	
	/* 执行任务 */
	vTaskStartScheduler();
}





/**********************************************************************创建任务************************************************************/

void Task_Create(void)
{
	taskENTER_CRITICAL();														// 进入任务临界区
	
	Test_Queue = xQueueCreate(TESET_QUEUE_SIZE,TESET_QUEUE_ITEM_SIZE);			// 创建测试消息队列
	
	/* LED任务 */
	xTaskCreate((TaskFunction_t	)LED_Task,										// 任务函数
				(const char*	)"LED_Task",									// 任务名称
				(u16			)LED_STK_SIZE,									// 任务堆栈大小
				(void*			)NULL,											// 传递给任务函数的参数
				(UBaseType_t	)LED_TASK_PRIO,									// 任务优先级
				(TaskHandle_t*	)&LEDTask_Handler);								// 任务句柄

				
	/* 系统监视任务 */
	xTaskCreate((TaskFunction_t	)Monitor_Task,									
				(const char*	)"Monitor_Task",								
				(u16			)Monitor_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)Monitor_TASK_PRIO,								
				(TaskHandle_t*	)&MonitorTask_Handler);		

	/* 状态发送任务 */
	xTaskCreate((TaskFunction_t	)StateDataSend_Task,									
				(const char*	)"StateDataSend_Task",								
				(u16			)StateDataSend_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)StateDataSend_TASK_PRIO,								
				(TaskHandle_t*	)&StateDataSendTask_Handler);	

	/* 通信任务 */
	xTaskCreate((TaskFunction_t	)Communicate_Task,									
				(const char*	)"Communicate_Task",								
				(u16			)Communicate_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)Communicate_TASK_PRIO,								
				(TaskHandle_t*	)&CommunicateTask_Handler);					
				
				
	taskEXIT_CRITICAL();														// 退出任务临界区
}





/**********************************************************************定义任务************************************************************/

/** --------------------------------------------------------------------------
  * @brief  系统监视任务
  
  * @retval None
  
  * @param	None
			
  * @note	1000ms执行一次
 -------------------------------------------------------------------------- **/
void Monitor_Task(void)
{
	static u32 TaskStartTime;													
	const TickType_t RouteTimes = pdMS_TO_TICKS(Monitor_TASK_CYCLE);			// 把执行周期转换为时间片个数
	
	while(1)
	{
		TaskStartTime = TIME();													// 记录任务执行的起始时刻（us）
		
		SystemMonitorDetect();													// 任务主体
		
		systemMonitor.SystemMonitorTask_cnt++;									// 记录任务执行次数
		systemMonitor.SystemMonitorTask_ExecuteTime = TIME() - TaskStartTime;	// 记录任务用时
		
		vTaskDelay(RouteTimes);													// 等待下一次运行
	}
}





/** --------------------------------------------------------------------------
  * @brief  LED状态切换任务
  
  * @retval None
  
  * @param	None
			
  * @note	500ms执行一次
 -------------------------------------------------------------------------- **/
void LED_Task(void)
{
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(LED_TASK_CYCLE);
	
	while(1)
	{
		TaskStartTime = TIME();

		LEDStateChange();		
		
		systemMonitor.LEDTask_cnt++;
		systemMonitor.LEDTask_ExecuteTime = TIME() - TaskStartTime;
		
		vTaskDelay(RouteTimes);
	}
}





/** --------------------------------------------------------------------------
  * @brief  状态数据发送任务
  
  * @retval None
  
  * @param	None
			
  * @note	10ms执行一次
 -------------------------------------------------------------------------- **/
void StateDataSend_Task(void)
{
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(StateDataSend_TASK_CYCLE);
	
	while(1)
	{
		TaskStartTime = TIME();
		
		StateDataSend();
		
		systemMonitor.StateDataSendTask_cnt++;
		systemMonitor.StateDataSendTask_ExecuteTime = TIME() - TaskStartTime;
		
		vTaskDelay(RouteTimes);
	}
}	





/** --------------------------------------------------------------------------
  * @brief  通信数据发送任务
  
  * @retval None
  
  * @param	None
			
  * @note	1ms执行一次
 -------------------------------------------------------------------------- **/
void Communicate_Task(void)
{
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(Communicate_TASK_CYCLE);
	
	while(1)
	{
		TaskStartTime = TIME();
		
		GimbalDataSend();
		
		systemMonitor.CommunicateTask_cnt++;
		systemMonitor.CommunicateTask_ExecuteTime = TIME() - TaskStartTime;
		
		vTaskDelay(RouteTimes);
	}
}	
