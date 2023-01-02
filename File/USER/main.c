#include "main.h"

/***********************************************************************������************************************************************/

int main(void)
{
	/* ��ʼ�� */
	BSP_Init();

	/* �������� */
	Task_Create();
	
	/* ִ������ */
	vTaskStartScheduler();
}





/**********************************************************************��������************************************************************/

void Task_Create(void)
{
	taskENTER_CRITICAL();														// ���������ٽ���
	
	Test_Queue = xQueueCreate(TESET_QUEUE_SIZE,TESET_QUEUE_ITEM_SIZE);			// ����������Ϣ����
	
	/* LED���� */
	xTaskCreate((TaskFunction_t	)LED_Task,										// ������
				(const char*	)"LED_Task",									// ��������
				(u16			)LED_STK_SIZE,									// �����ջ��С
				(void*			)NULL,											// ���ݸ��������Ĳ���
				(UBaseType_t	)LED_TASK_PRIO,									// �������ȼ�
				(TaskHandle_t*	)&LEDTask_Handler);								// ������

				
	/* ϵͳ�������� */
	xTaskCreate((TaskFunction_t	)Monitor_Task,									
				(const char*	)"Monitor_Task",								
				(u16			)Monitor_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)Monitor_TASK_PRIO,								
				(TaskHandle_t*	)&MonitorTask_Handler);		

	/* ״̬�������� */
	xTaskCreate((TaskFunction_t	)StateDataSend_Task,									
				(const char*	)"StateDataSend_Task",								
				(u16			)StateDataSend_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)StateDataSend_TASK_PRIO,								
				(TaskHandle_t*	)&StateDataSendTask_Handler);	

	/* ͨ������ */
	xTaskCreate((TaskFunction_t	)Communicate_Task,									
				(const char*	)"Communicate_Task",								
				(u16			)Communicate_STK_SIZE,								
				(void*			)NULL,											
				(UBaseType_t	)Communicate_TASK_PRIO,								
				(TaskHandle_t*	)&CommunicateTask_Handler);					
				
				
	taskEXIT_CRITICAL();														// �˳������ٽ���
}





/**********************************************************************��������************************************************************/

/** --------------------------------------------------------------------------
  * @brief  ϵͳ��������
  
  * @retval None
  
  * @param	None
			
  * @note	1000msִ��һ��
 -------------------------------------------------------------------------- **/
void Monitor_Task(void)
{
	static u32 TaskStartTime;													
	const TickType_t RouteTimes = pdMS_TO_TICKS(Monitor_TASK_CYCLE);			// ��ִ������ת��Ϊʱ��Ƭ����
	
	while(1)
	{
		TaskStartTime = TIME();													// ��¼����ִ�е���ʼʱ�̣�us��
		
		SystemMonitorDetect();													// ��������
		
		systemMonitor.SystemMonitorTask_cnt++;									// ��¼����ִ�д���
		systemMonitor.SystemMonitorTask_ExecuteTime = TIME() - TaskStartTime;	// ��¼������ʱ
		
		vTaskDelay(RouteTimes);													// �ȴ���һ������
	}
}





/** --------------------------------------------------------------------------
  * @brief  LED״̬�л�����
  
  * @retval None
  
  * @param	None
			
  * @note	500msִ��һ��
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
  * @brief  ״̬���ݷ�������
  
  * @retval None
  
  * @param	None
			
  * @note	10msִ��һ��
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
  * @brief  ͨ�����ݷ�������
  
  * @retval None
  
  * @param	None
			
  * @note	1msִ��һ��
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
