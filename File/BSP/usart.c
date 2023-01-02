#include "usart.h"	
#include "global_declare.h"
#include <stdio.h>

//加入以下代码,并选择使用MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 



/** --------------------------------------------------------------------------
  * @brief  串口2初始化
  
  * @retval None
  
  * @param	None
			
  * @note	DMA发送+空闲中断
			配合打印函数使用
 -------------------------------------------------------------------------- **/
void usart2_init(void)
{
	/*定义初始化相关结构体*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef 	DMA_InitStructure;

	
	/*配置时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_DMA1,ENABLE);				// 使能PD端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);									// 使能USART2时钟
	
	
	/*配置端口复用*/	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); 

	
	/*配置GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;											// 复用模式
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;										// 推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;									// IO口速度为100MHz
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;										// 浮空输入
	GPIO_Init(GPIOD,&GPIO_InitStructure);													// 根据设定参数初始化GPIOA
	
	
	/*配置串口*/
	USART_InitStructure.USART_BaudRate 				= 115200;								// 波特率
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;					// 字长为8位数据格式
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;						// 一个停止位
	USART_InitStructure.USART_Parity 				= USART_Parity_No;						// 无奇偶校验位
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx|USART_Mode_Rx;			// 收发模式
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;		// 无硬件数据流控制
	USART_Init(USART2,&USART_InitStructure);												//初始化串口

	
	/*配置中断*/
	NVIC_InitStructure.NVIC_IRQChannel 						= USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 5;							// 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;							// 子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;						// IRQ通道使能 
	NVIC_Init(&NVIC_InitStructure);															// 根据指定的参数初始化VIC寄存器
	
	
	/*配置发送DMA*/
	DMA_DeInit(USART2_TX_STREAM);
	while( DMA_GetCmdStatus(USART2_TX_STREAM) == ENABLE);									// 等待DMA可配置
	
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&(USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr 		= NULL;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;				// 内存到外设
	DMA_InitStructure.DMA_BufferSize 			= 0;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;				// 固定外设基地址
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;						// 内存递增发送
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Normal;							// 普通模式发送
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(USART2_TX_STREAM, &DMA_InitStructure);


	/*使能串口、DMA、中断*/
	USART_Cmd(USART2, ENABLE);  															// 使能串口2
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);											// 使能空闲中断	
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);											// 使能串口2发送DMA
	DMA_Cmd(USART2_TX_STREAM, ENABLE);														// 失能发送DMA(进行发送时再打开)

}



/** --------------------------------------------------------------------------
  * @brief  串口3初始化
  
  * @retval None
  
  * @param	None
			
  * @note	用于和云台进行通信
 -------------------------------------------------------------------------- **/
void usart3_init(void)
{
	/*定义初始化相关结构体*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef		DMA_InitStructure;


	/*配置时钟*/	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 										// 使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);										// 使能USART3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);											// 使能DMA1时钟
 
	
	/*配置端口复用*/
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); 									// GPIOD8复用为USART3 TX
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 									// GPIOD9复用为USART3 RX
	
	
	/*配置GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_9; 									// GPIOD8 GPIOD9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;												// 复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;											// 速度50MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_OD; 											// 推挽复用输出
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 											// 上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); 														// 初始化PD8 PD9


	/*配置串口*/
	USART_DeInit(USART3);
	USART_InitStructure.USART_BaudRate 				= 460800;									// 波特率设置
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;						// 字长为8位数据格式
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;							// 一个停止位
	USART_InitStructure.USART_Parity 				= USART_Parity_No;							// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;			// 无硬件数据流控制
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx | USART_Mode_Rx;			// 收发模式
	USART_Init(USART3, &USART_InitStructure); 													// 初始化串口3
	

	/*配置中断*/
	NVIC_InitStructure.NVIC_IRQChannel 						= USART3_IRQn;						// 串口3中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 5;								// 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;								// 子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;							// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);																// 根据指定的参数初始化NVIC寄存器


	/*配置接收DMA*/
	DMA_DeInit(USART3_RX_STREAM);
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)&(USART3->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (u32)&UA3RxDMAbuf;	
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize 			= UA3RxDMAbuf_LEN;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(USART3_RX_STREAM, &DMA_InitStructure);
	
	/*配置发送DMA*/
	DMA_DeInit(USART3_TX_STREAM);
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)&(USART3->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr 		= NULL; 
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize 			= 0;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(USART3_TX_STREAM, &DMA_InitStructure);

	/*使能串口、DMA、中断*/
	USART_Cmd(USART3, ENABLE);  															// 使能串口3
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);											// 使能空闲中断	
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);											// 使能串口3接收DMA
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);											// 使能串口3发送DMA
	DMA_Cmd(USART3_RX_STREAM, ENABLE);														// 使能接收DMA
	DMA_Cmd(USART3_TX_STREAM, DISABLE);														// 失能发送DMA(进行发送时再打开)
}






/** --------------------------------------------------------------------------
  * @brief  串口4初始化
  
  * @retval None
  
  * @param	None
			
  * @note	用于向上位机发送状态数据
 -------------------------------------------------------------------------- **/
void uart4_init(void)
{
	/*定义初始化相关结构体*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef 	DMA_InitStructure;


	/*配置时钟*/		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 									// 使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);									// 使能UART4时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);										// 使能DMA1时钟
 
	
	/*配置端口复用*/
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); 								// GPIOC10复用为UART4 TX
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); 								// GPIOC11复用为UART4 RX
	
	
	/*配置GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11; 							// GPIOC10 GPIOC11
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;											// 复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;										// 速度50MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_OD; 										// 推挽复用输出
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure); 													// 初始化PC10 PC11

	/*配置串口*/
	USART_DeInit(UART4);
	USART_InitStructure.USART_BaudRate 				= 115200;								// 波特率设置
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;					// 字长为8位数据格式
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;						// 一个停止位 
	USART_InitStructure.USART_Parity 				= USART_Parity_No;						// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;		// 无硬件数据流控制
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx | USART_Mode_Rx;		// 接收模式
	USART_Init(UART4, &USART_InitStructure); 												// 初始化串口4
	

	/*配置中断*/
	NVIC_InitStructure.NVIC_IRQChannel 						= UART4_IRQn;					// 串口4中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;							// 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;							// 子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;						// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);															// 根据指定的参数初始化NVIC寄存器


	/*配置接收DMA*/
	DMA_InitStructure.DMA_PeripheralBaseAddr      =    (uint32_t)&(UART4->DR);				// 设置DMA传输外设基地址（把DMA应用于串口1的接收中）
    DMA_InitStructure.DMA_Memory0BaseAddr         =    (uint32_t)UA4RxDMAbuf;				// 设置DMA传输内存基地址（用户自定义，串口1接收到的数据将存在这里面）
    DMA_InitStructure.DMA_DIR                     =    DMA_DIR_PeripheralToMemory;			// 设置数据传输方向（外设接收到内存）
    DMA_InitStructure.DMA_BufferSize              =    UA4RxDMAbuf_LEN;						// 设置DMA一次传输数据量的大小（500字节）
    DMA_InitStructure.DMA_PeripheralInc           =    DMA_PeripheralInc_Disable;			// 设置外设地址不变
    DMA_InitStructure.DMA_MemoryInc               =    DMA_MemoryInc_Enable;				// 设置内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize      =    DMA_PeripheralDataSize_Byte;			// 设置外设的数据长度为字节（8bits）
    DMA_InitStructure.DMA_MemoryDataSize          =    DMA_MemoryDataSize_Byte;				// 设置内存的数据长度为字节（8bits）
    DMA_InitStructure.DMA_Mode                    =    DMA_Mode_Normal;						// 设置DMA模式为循环模式
    DMA_InitStructure.DMA_Priority                =    DMA_Priority_VeryHigh;				// 设置DMA通道的优先级为最高优先级
    DMA_InitStructure.DMA_FIFOMode                =    DMA_FIFOMode_Disable;				// 不使用FIFO模式
    DMA_InitStructure.DMA_FIFOThreshold           =    DMA_FIFOThreshold_1QuarterFull;		// FIFO阈值
    DMA_InitStructure.DMA_MemoryBurst             =    DMA_MemoryBurst_Single;				
    DMA_InitStructure.DMA_PeripheralBurst         =    DMA_PeripheralBurst_Single;			// 外设突发单次传输
	DMA_Init(UART4_RX_STREAM, &DMA_InitStructure);
	
	
	/*配置发送DMA*/
	DMA_DeInit(UART4_TX_STREAM);
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)&(UART4->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr 		= NULL; 
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize 			= 0;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(UART4_TX_STREAM, &DMA_InitStructure);


	/*使能串口、DMA、中断*/
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);											// 开启空闲中断	
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);											// 使能串口4的接收DMA
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);											// 使能串口4的接发送DMA
	USART_Cmd(UART4, ENABLE);  																// 使能串口4
	DMA_Cmd(UART4_RX_STREAM, ENABLE);														// 使能接收DMA
	DMA_Cmd(UART4_TX_STREAM, DISABLE);														// 失能发送DMA(进行发送时再打开)
}
