#include "can.h"



/*-------------------------------------------------------
CAN1			|	Rx              |	Tx			    |
---------------------------------------------------------
引脚			|	PB8		    	|	PB9	    		|
中断优先级		|	抢0子3		    |	抢0子2		    |
波特率			|	42M			    |	42M			    |
---------------------------------------------------------
功能			|   底盘主动轮电机、下云台YAW电机		|
---------------------------------------------------------

---------------------------------------------------------
CAN2			|	Rx              |	Tx			    |
---------------------------------------------------------
引脚			|	PB5           	| 	PB6		   	 	|
中断优先级		|	抢0子4		    |	抢1子6		    |
波特率			|	42M			    |	42M			    |
---------------------------------------------------------
功能			|	上云台拨弹电机、上云台Yaw电机   	|
-------------------------------------------------------*/




/** --------------------------------------------------------------------------
  * @brief  初始化CAN1
			
  * @note	引脚	：PB8(CAN1_RX);PB9(CAN1_TX)
			波特率	：1MHz
			计算公式BaudRate = 42MHz/Prescaler*(1+BS1+BS2)
			CAN1波特率=42MHz/3/(9+4+1)=1MHz
 -------------------------------------------------------------------------- **/
void CAN1_Configuration(void)
{
	/*定义初始化结构体*/
    GPIO_InitTypeDef       gpio = {0};											// 定义GPIO初始化结构体
    NVIC_InitTypeDef       nvic = {0};											// 定义中断优先级初始化结构体
    CAN_InitTypeDef        can1 = {0};											// 定义CAN初始化结构体
    CAN_FilterInitTypeDef  can1_filter = {0};									// 定义CAN的ID过滤器初始化结构体

	
	/*配置时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   					// 使能PB端口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);   					// 使能CAN1时钟,42MHz

	
	/*配置端口复用*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);						// GPIO口端口复用为CAN通信端口
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);

	
	/*配置GPIO*/
    gpio.GPIO_Pin   							= GPIO_Pin_8 | GPIO_Pin_9;		// 设置初始化的CAN引脚号
    gpio.GPIO_Mode  							= GPIO_Mode_AF;					// 端口复用模式
    GPIO_Init(GPIOB, &gpio);													// 根据指定的参数初始化GPIO寄存器
    
	
	/*配置接收中断*/
    nvic.NVIC_IRQChannel                    	= CAN1_RX0_IRQn;				// 接收中断服务函数入口
    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// 抢占优先级
    nvic.NVIC_IRQChannelSubPriority         	= 3;        					// 子优先级
    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQ通道使能
    NVIC_Init(&nvic);   														// 根据指定的参数初始化NVIC寄存器
    
	
//	/*配置发送中断（暂未使用）*/	
//    nvic.NVIC_IRQChannel                    	= CAN1_TX_IRQn;					// 发送中断服务函数入口
//    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// 抢占优先级
//    nvic.NVIC_IRQChannelSubPriority         	= 2;        					// 子优先级
//    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQ通道使能
//    NVIC_Init(&nvic);   														// 根据指定的参数初始化NVIC寄存器
 
 
	/*配置CAN相关寄存器*/
    CAN_DeInit(CAN1);															// 重置CAN寄存器
    CAN_StructInit(&can1); 														// 为CAN初始化结构体赋初始值  
	/* CAN主控制寄存器器（CAN_MCR）*/
    can1.CAN_TTCM = DISABLE;        											// 时间触发通信模式
    can1.CAN_ABOM = DISABLE;        											// 自动的总线关闭管理
    can1.CAN_AWUM = DISABLE;        											// 自动唤醒模式
    can1.CAN_NART = DISABLE;        											// 禁止自动重发送
    can1.CAN_RFLM = DISABLE;        											// 接收FIFO锁定模式
    can1.CAN_TXFP = ENABLE;         											// 发送FIFIO优先级
	/* CAN位时序寄存器（CAN_BTR）*/
    can1.CAN_Mode 								= CAN_Mode_Normal;				// 普通模式
    can1.CAN_SJW  								= CAN_SJW_1tq;    				// 重新同步跳跃宽度
    can1.CAN_BS1  								= CAN_BS1_9tq;    				// 时间段1
    can1.CAN_BS2  								= CAN_BS2_4tq;    				// 时间段2
    can1.CAN_Prescaler 							= 3;         					// 分频系数
    CAN_Init(CAN1, &can1);          											// 根据指定的参数初始化CAN寄存器(CAN1波特率=42MHz/3/(9+4+1)=1MHz)
	/* CAN过滤器 */
    can1_filter.CAN_FilterNumber         		= 0;                       		// 过滤器0
    can1_filter.CAN_FilterMode          		= CAN_FilterMode_IdMask;   		// 标识符过滤器为掩码模式
    can1_filter.CAN_FilterScale          		= CAN_FilterScale_32bit;   		// 一个32位标识符过滤器
    can1_filter.CAN_FilterIdHigh         		= 0x0000;                  		// 32位标识符过滤器的高16位
    can1_filter.CAN_FilterIdLow          		= 0x0000;                  		// 32位标识符过滤器的低16位
    can1_filter.CAN_FilterMaskIdHigh     		= 0x0000;                  		// 过滤器掩码高16位
    can1_filter.CAN_FilterMaskIdLow      		= 0x0000;                  		// 过滤器掩码低16位
    can1_filter.CAN_FilterFIFOAssignment 		= CAN_Filter_FIFO0;        		// 过滤器0关联到FIFO0
    can1_filter.CAN_FilterActivation     		= ENABLE;                  		// 激活过滤器
    CAN_FilterInit(&can1_filter);             									// 根据指定的参数初始化CAN_Filter寄存器
    
	
	/*CAN中断使能*/
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  									// 接收中断:FIFO 0消息挂起中断（相当于空闲中断）
//    CAN_ITConfig(CAN1, CAN_IT_TME,  ENABLE);  								// 发送中断：发送邮箱空中断 
}





/** --------------------------------------------------------------------------
  * @brief  初始化CAN2
  
  * @note	引脚	：PB5(CAN2_RX);PB6(CAN2_TX)
			波特率	：1MHz
			计算公式BaudRate = 42MHz/Prescaler*(1+BS1+BS2)
			CAN2波特率=42MHz/3/(9+4+1)=1MHz
 -------------------------------------------------------------------------- **/
void CAN2_Configuration(void)
{
	/*定义初始化结构体*/
    GPIO_InitTypeDef       gpio = {0};											// 定义GPIO初始化结构体
    NVIC_InitTypeDef       nvic = {0};											// 定义中断优先级初始化结构体
    CAN_InitTypeDef        can2 = {0};											// 定义CAN初始化结构体
    CAN_FilterInitTypeDef  can2_filter = {0};									// 定义CAN的ID过滤器初始化结构体

	
	/*配置时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   					// 使能PB端口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);   					// 使能CAN1时钟,42MHz(单独使用CAN2时需要先使能CAN1的时钟)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,  ENABLE);   					// 使能CAN2时钟,42MHz

	
	/*配置端口复用*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);						// GPIO口端口复用为CAN通信端口
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);

	
	/*配置GPIO*/
    gpio.GPIO_Pin   							= GPIO_Pin_5 | GPIO_Pin_6;		// 设置初始化的CAN引脚号
    gpio.GPIO_Mode  							= GPIO_Mode_AF;					// 端口复用模式
    GPIO_Init(GPIOB, &gpio);													// 根据指定的参数初始化GPIO寄存器


	/*配置接收中断*/
    nvic.NVIC_IRQChannel                    	= CAN2_RX0_IRQn;				// 接收中断服务函数入口
    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// 抢占优先级
    nvic.NVIC_IRQChannelSubPriority         	= 4;        					// 子优先级
    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQ通道使能
    NVIC_Init(&nvic);   														// 根据指定的参数初始化NVIC寄存器
    
	
//	/*配置发送中断（暂未使用）*/	
//    nvic.NVIC_IRQChannel                    	= CAN2_TX_IRQn;					// 发送中断服务函数入口
//    nvic.NVIC_IRQChannelPreemptionPriority  	= 1;        					// 抢占优先级
//    nvic.NVIC_IRQChannelSubPriority         	= 6;        					// 子优先级
//    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQ通道使能
//    NVIC_Init(&nvic);   														// 根据指定的参数初始化NVIC寄存器
 
 
	/*配置CAN相关寄存器*/
    CAN_DeInit(CAN2);															// 重置CAN寄存器
    CAN_StructInit(&can2); 														// 为CAN初始化结构体赋初始值  
	/* CAN主控制寄存器器（CAN_MCR）*/
    can2.CAN_TTCM = DISABLE;        											// 时间触发通信模式
    can2.CAN_ABOM = DISABLE;        											// 自动的总线关闭管理
    can2.CAN_AWUM = DISABLE;        											// 自动唤醒模式
    can2.CAN_NART = DISABLE;        											// 禁止自动重发送
    can2.CAN_RFLM = DISABLE;        											// 接收FIFO锁定模式
    can2.CAN_TXFP = ENABLE;         											// 发送FIFIO优先级
	/* CAN位时序寄存器（CAN_BTR）*/
    can2.CAN_Mode 								= CAN_Mode_Normal;				// 普通模式
    can2.CAN_SJW  								= CAN_SJW_1tq;    				// 重新同步跳跃宽度
    can2.CAN_BS1  								= CAN_BS1_9tq;    				// 时间段1
    can2.CAN_BS2  								= CAN_BS2_4tq;    				// 时间段2
    can2.CAN_Prescaler 							= 3;         					// 分频系数
    CAN_Init(CAN2, &can2);          											// 根据指定的参数初始化CAN寄存器(CAN2波特率=42MHz/3/(9+4+1)=1MHz)
	/* CAN过滤器 */
    can2_filter.CAN_FilterNumber         		= 14;                       	// 过滤器
    can2_filter.CAN_FilterMode          		= CAN_FilterMode_IdMask;   		// 标识符过滤器为掩码模式
    can2_filter.CAN_FilterScale          		= CAN_FilterScale_32bit;   		// 一个32位标识符过滤器
    can2_filter.CAN_FilterIdHigh         		= 0x0000;                  		// 32位标识符过滤器的高16位
    can2_filter.CAN_FilterIdLow          		= 0x0000;                  		// 32位标识符过滤器的低16位
    can2_filter.CAN_FilterMaskIdHigh     		= 0x0000;                  		// 过滤器掩码高16位
    can2_filter.CAN_FilterMaskIdLow      		= 0x0000;                  		// 过滤器掩码低16位
    can2_filter.CAN_FilterFIFOAssignment 		= CAN_Filter_FIFO0;        		// 过滤器0关联到FIFO0
    can2_filter.CAN_FilterActivation     		= ENABLE;                  		// 激活过滤器
    CAN_FilterInit(&can2_filter);             									// 根据指定的参数初始化CAN_Filter寄存器
    
	
	/*CAN中断使能*/
    CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);  									// 接收中断:FIFO 0消息挂起中断（类似于空闲中断）
//    CAN_ITConfig(CAN2, CAN_IT_TME,  ENABLE);  								// 发送中断：发送邮箱空中断 
}


