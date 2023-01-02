#include "bsp_init.h"
#include "delay.h"
#include "systick.h"
#include "usart.h"
#include "tim.h"
#include "led.h"


/** --------------------------------------------------------------------------
  * @brief  ��ʼ������
			
  * @note	������������г�ʼ��
 -------------------------------------------------------------------------- **/
void BSP_Init(void)
{
	/** �����ж���� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);					// 16���������ȼ���0�������ȼ�
	
	/** us��ʱ����ʼ�� */
	TIM5_Configuration();

	/** LED��ʼ�� */
	led_init();
	
	/** ���ڳ�ʼ�� */
	usart2_init();
	usart3_init();
	uart4_init();

}






