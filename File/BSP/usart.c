#include "usart.h"	
#include "global_declare.h"
#include <stdio.h>

//�������´���,��ѡ��ʹ��MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 



/** --------------------------------------------------------------------------
  * @brief  ����2��ʼ��
  
  * @retval None
  
  * @param	None
			
  * @note	DMA����+�����ж�
			��ϴ�ӡ����ʹ��
 -------------------------------------------------------------------------- **/
void usart2_init(void)
{
	/*�����ʼ����ؽṹ��*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef 	DMA_InitStructure;

	
	/*����ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_DMA1,ENABLE);				// ʹ��PD�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);									// ʹ��USART2ʱ��
	
	
	/*���ö˿ڸ���*/	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); 

	
	/*����GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;											// ����ģʽ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;										// �������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;									// IO���ٶ�Ϊ100MHz
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;										// ��������
	GPIO_Init(GPIOD,&GPIO_InitStructure);													// �����趨������ʼ��GPIOA
	
	
	/*���ô���*/
	USART_InitStructure.USART_BaudRate 				= 115200;								// ������
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;					// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;						// һ��ֹͣλ
	USART_InitStructure.USART_Parity 				= USART_Parity_No;						// ����żУ��λ
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx|USART_Mode_Rx;			// �շ�ģʽ
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;		// ��Ӳ������������
	USART_Init(USART2,&USART_InitStructure);												//��ʼ������

	
	/*�����ж�*/
	NVIC_InitStructure.NVIC_IRQChannel 						= USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 5;							// ��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;							// �����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;						// IRQͨ��ʹ�� 
	NVIC_Init(&NVIC_InitStructure);															// ����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	/*���÷���DMA*/
	DMA_DeInit(USART2_TX_STREAM);
	while( DMA_GetCmdStatus(USART2_TX_STREAM) == ENABLE);									// �ȴ�DMA������
	
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&(USART2->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr 		= NULL;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;				// �ڴ浽����
	DMA_InitStructure.DMA_BufferSize 			= 0;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;				// �̶��������ַ
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;						// �ڴ��������
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Normal;							// ��ͨģʽ����
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(USART2_TX_STREAM, &DMA_InitStructure);


	/*ʹ�ܴ��ڡ�DMA���ж�*/
	USART_Cmd(USART2, ENABLE);  															// ʹ�ܴ���2
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);											// ʹ�ܿ����ж�	
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);											// ʹ�ܴ���2����DMA
	DMA_Cmd(USART2_TX_STREAM, ENABLE);														// ʧ�ܷ���DMA(���з���ʱ�ٴ�)

}



/** --------------------------------------------------------------------------
  * @brief  ����3��ʼ��
  
  * @retval None
  
  * @param	None
			
  * @note	���ں���̨����ͨ��
 -------------------------------------------------------------------------- **/
void usart3_init(void)
{
	/*�����ʼ����ؽṹ��*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef		DMA_InitStructure;


	/*����ʱ��*/	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 										// ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);										// ʹ��USART3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);											// ʹ��DMA1ʱ��
 
	
	/*���ö˿ڸ���*/
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); 									// GPIOD8����ΪUSART3 TX
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 									// GPIOD9����ΪUSART3 RX
	
	
	/*����GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_9; 									// GPIOD8 GPIOD9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;												// ���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;											// �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_OD; 											// ���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 											// ����
	GPIO_Init(GPIOD,&GPIO_InitStructure); 														// ��ʼ��PD8 PD9


	/*���ô���*/
	USART_DeInit(USART3);
	USART_InitStructure.USART_BaudRate 				= 460800;									// ����������
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity 				= USART_Parity_No;							// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;			// ��Ӳ������������
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx | USART_Mode_Rx;			// �շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); 													// ��ʼ������3
	

	/*�����ж�*/
	NVIC_InitStructure.NVIC_IRQChannel 						= USART3_IRQn;						// ����3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 5;								// ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;								// �����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;							// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);																// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���


	/*���ý���DMA*/
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
	
	/*���÷���DMA*/
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

	/*ʹ�ܴ��ڡ�DMA���ж�*/
	USART_Cmd(USART3, ENABLE);  															// ʹ�ܴ���3
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);											// ʹ�ܿ����ж�	
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);											// ʹ�ܴ���3����DMA
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);											// ʹ�ܴ���3����DMA
	DMA_Cmd(USART3_RX_STREAM, ENABLE);														// ʹ�ܽ���DMA
	DMA_Cmd(USART3_TX_STREAM, DISABLE);														// ʧ�ܷ���DMA(���з���ʱ�ٴ�)
}






/** --------------------------------------------------------------------------
  * @brief  ����4��ʼ��
  
  * @retval None
  
  * @param	None
			
  * @note	��������λ������״̬����
 -------------------------------------------------------------------------- **/
void uart4_init(void)
{
	/*�����ʼ����ؽṹ��*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	DMA_InitTypeDef 	DMA_InitStructure;


	/*����ʱ��*/		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 									// ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);									// ʹ��UART4ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);										// ʹ��DMA1ʱ��
 
	
	/*���ö˿ڸ���*/
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); 								// GPIOC10����ΪUART4 TX
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); 								// GPIOC11����ΪUART4 RX
	
	
	/*����GPIO*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10 | GPIO_Pin_11; 							// GPIOC10 GPIOC11
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;											// ���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;										// �ٶ�50MHz
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_OD; 										// ���츴�����
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure); 													// ��ʼ��PC10 PC11

	/*���ô���*/
	USART_DeInit(UART4);
	USART_InitStructure.USART_BaudRate 				= 115200;								// ����������
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;					// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;						// һ��ֹͣλ 
	USART_InitStructure.USART_Parity 				= USART_Parity_No;						// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;		// ��Ӳ������������
	USART_InitStructure.USART_Mode 					= USART_Mode_Tx | USART_Mode_Rx;		// ����ģʽ
	USART_Init(UART4, &USART_InitStructure); 												// ��ʼ������4
	

	/*�����ж�*/
	NVIC_InitStructure.NVIC_IRQChannel 						= UART4_IRQn;					// ����4�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;							// ��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;							// �����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;						// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���


	/*���ý���DMA*/
	DMA_InitStructure.DMA_PeripheralBaseAddr      =    (uint32_t)&(UART4->DR);				// ����DMA�����������ַ����DMAӦ���ڴ���1�Ľ����У�
    DMA_InitStructure.DMA_Memory0BaseAddr         =    (uint32_t)UA4RxDMAbuf;				// ����DMA�����ڴ����ַ���û��Զ��壬����1���յ������ݽ����������棩
    DMA_InitStructure.DMA_DIR                     =    DMA_DIR_PeripheralToMemory;			// �������ݴ��䷽��������յ��ڴ棩
    DMA_InitStructure.DMA_BufferSize              =    UA4RxDMAbuf_LEN;						// ����DMAһ�δ����������Ĵ�С��500�ֽڣ�
    DMA_InitStructure.DMA_PeripheralInc           =    DMA_PeripheralInc_Disable;			// ���������ַ����
    DMA_InitStructure.DMA_MemoryInc               =    DMA_MemoryInc_Enable;				// �����ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize      =    DMA_PeripheralDataSize_Byte;			// ������������ݳ���Ϊ�ֽڣ�8bits��
    DMA_InitStructure.DMA_MemoryDataSize          =    DMA_MemoryDataSize_Byte;				// �����ڴ�����ݳ���Ϊ�ֽڣ�8bits��
    DMA_InitStructure.DMA_Mode                    =    DMA_Mode_Normal;						// ����DMAģʽΪѭ��ģʽ
    DMA_InitStructure.DMA_Priority                =    DMA_Priority_VeryHigh;				// ����DMAͨ�������ȼ�Ϊ������ȼ�
    DMA_InitStructure.DMA_FIFOMode                =    DMA_FIFOMode_Disable;				// ��ʹ��FIFOģʽ
    DMA_InitStructure.DMA_FIFOThreshold           =    DMA_FIFOThreshold_1QuarterFull;		// FIFO��ֵ
    DMA_InitStructure.DMA_MemoryBurst             =    DMA_MemoryBurst_Single;				
    DMA_InitStructure.DMA_PeripheralBurst         =    DMA_PeripheralBurst_Single;			// ����ͻ�����δ���
	DMA_Init(UART4_RX_STREAM, &DMA_InitStructure);
	
	
	/*���÷���DMA*/
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


	/*ʹ�ܴ��ڡ�DMA���ж�*/
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);											// ���������ж�	
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);											// ʹ�ܴ���4�Ľ���DMA
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);											// ʹ�ܴ���4�Ľӷ���DMA
	USART_Cmd(UART4, ENABLE);  																// ʹ�ܴ���4
	DMA_Cmd(UART4_RX_STREAM, ENABLE);														// ʹ�ܽ���DMA
	DMA_Cmd(UART4_TX_STREAM, DISABLE);														// ʧ�ܷ���DMA(���з���ʱ�ٴ�)
}
