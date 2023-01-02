#include "exti.h"
#include "rm_robot_types.h"
#include "global_declare.h"

/** @brief 外部中断9使能失能配置
 */
void EXTI1_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	 /* 配置EXTI_Line9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;//LINE9
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
	stFlag.EXTI1_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
}

/** @brief 外部中断10使能失能配置
 */
void EXTI2_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	/* 配置EXTI_Line10 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
 	stFlag.EXTI2_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
}

/** @brief 外部中断11使能失能配置
 */
void EXTI3_Cmd(FunctionalState NewState)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	/* 配置EXTI_Line11 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
 	stFlag.EXTI2_IT_ENABLE_FLAG = (bool)NewState;
	EXTI_InitStructure.EXTI_LineCmd = NewState;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
}





/** --------------------------------------------------------------------------
  * @brief  光电门初始化
  
  * @retval None
  
  * @param	None
			
  * @note	光电门用于撞柱检测和标定轨道位置
			PE7/8/9
 -------------------------------------------------------------------------- **/
void PhotoGate_GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);				// 使能GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;						// 普通输入模式
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;				// 100M
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;						// 上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);								// 初始化GPIO
}







///** @brief 外部中断引脚初始化配置
// */
//void EXTI_Configuration(void)
//{
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

//	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;//普通输入模式
//	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;//100M
//	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;//上拉
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
//		
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);	//PE9  连接到中断线9
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);	//PE10 连接到中断线10
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource11);	//PE11 连接到中断线11
//	
//	EXTI1_Cmd(ENABLE);
//	EXTI2_Cmd(ENABLE);
//	EXTI3_Cmd(ENABLE);
//	
//	NVIC_InitStructure.NVIC_IRQChannel 						= EXTI9_5_IRQn;//外部中断5——9
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0x00;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0x06;//子优先级6
//	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel 						= EXTI15_10_IRQn;//外部中断10——15
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0x00;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0x07;//子优先级7
//	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);//配置
//}




