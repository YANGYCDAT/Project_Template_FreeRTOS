#include "exti.h"
#include "rm_robot_types.h"
#include "global_declare.h"

/** @brief �ⲿ�ж�9ʹ��ʧ������
 */
void EXTI1_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	 /* ����EXTI_Line9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;//LINE9
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
	stFlag.EXTI1_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
}

/** @brief �ⲿ�ж�10ʹ��ʧ������
 */
void EXTI2_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	/* ����EXTI_Line10 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
 	stFlag.EXTI2_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
}

/** @brief �ⲿ�ж�11ʹ��ʧ������
 */
void EXTI3_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	/* ����EXTI_Line11 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
 	stFlag.EXTI2_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
}





/** --------------------------------------------------------------------------
  * @brief  ����ų�ʼ��
  
  * @retval None
  
  * @param	None
			
  * @note	���������ײ�����ͱ궨���λ��
			PE7/8/9
 -------------------------------------------------------------------------- **/
void PhotoGate_GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);				// ʹ��GPIOEʱ��
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;						// ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;				// 100M
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;						// ����
	GPIO_Init(GPIOE, &GPIO_InitStructure);								// ��ʼ��GPIO
}







///** @brief �ⲿ�ж����ų�ʼ������
// */
//void EXTI_Configuration(void)
//{
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��

//	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;//��ͨ����ģʽ
//	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;//100M
//	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
//		
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);	//PE9  ���ӵ��ж���9
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);	//PE10 ���ӵ��ж���10
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);	//PE11 ���ӵ��ж���11
//	
//	EXTI1_Cmd(ENABLE);
//	EXTI2_Cmd(ENABLE);
//	EXTI3_Cmd(ENABLE);
//	
//	NVIC_InitStructure.NVIC_IRQChannel 						= EXTI9_5_IRQn;//�ⲿ�ж�5����9
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0x00;//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0x06;//�����ȼ�6
//	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel 						= EXTI15_10_IRQn;//�ⲿ�ж�10����15
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0x00;//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0x07;//�����ȼ�7
//	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);//����
//}




