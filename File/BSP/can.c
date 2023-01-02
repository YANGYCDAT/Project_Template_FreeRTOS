#include "can.h"



/*-------------------------------------------------------
CAN1			|	Rx              |	Tx			    |
---------------------------------------------------------
����			|	PB8		    	|	PB9	    		|
�ж����ȼ�		|	��0��3		    |	��0��2		    |
������			|	42M			    |	42M			    |
---------------------------------------------------------
����			|   ���������ֵ��������̨YAW���		|
---------------------------------------------------------

---------------------------------------------------------
CAN2			|	Rx              |	Tx			    |
---------------------------------------------------------
����			|	PB5           	| 	PB6		   	 	|
�ж����ȼ�		|	��0��4		    |	��1��6		    |
������			|	42M			    |	42M			    |
---------------------------------------------------------
����			|	����̨�������������̨Yaw���   	|
-------------------------------------------------------*/




/** --------------------------------------------------------------------------
  * @brief  ��ʼ��CAN1
			
  * @note	����	��PB8(CAN1_RX);PB9(CAN1_TX)
			������	��1MHz
			���㹫ʽBaudRate = 42MHz/Prescaler*(1+BS1+BS2)
			CAN1������=42MHz/3/(9+4+1)=1MHz
 -------------------------------------------------------------------------- **/
void CAN1_Configuration(void)
{
	/*�����ʼ���ṹ��*/
    GPIO_InitTypeDef       gpio = {0};											// ����GPIO��ʼ���ṹ��
    NVIC_InitTypeDef       nvic = {0};											// �����ж����ȼ���ʼ���ṹ��
    CAN_InitTypeDef        can1 = {0};											// ����CAN��ʼ���ṹ��
    CAN_FilterInitTypeDef  can1_filter = {0};									// ����CAN��ID��������ʼ���ṹ��

	
	/*����ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   					// ʹ��PB�˿�ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);   					// ʹ��CAN1ʱ��,42MHz

	
	/*���ö˿ڸ���*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);						// GPIO�ڶ˿ڸ���ΪCANͨ�Ŷ˿�
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);

	
	/*����GPIO*/
    gpio.GPIO_Pin   							= GPIO_Pin_8 | GPIO_Pin_9;		// ���ó�ʼ����CAN���ź�
    gpio.GPIO_Mode  							= GPIO_Mode_AF;					// �˿ڸ���ģʽ
    GPIO_Init(GPIOB, &gpio);													// ����ָ���Ĳ�����ʼ��GPIO�Ĵ���
    
	
	/*���ý����ж�*/
    nvic.NVIC_IRQChannel                    	= CAN1_RX0_IRQn;				// �����жϷ��������
    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// ��ռ���ȼ�
    nvic.NVIC_IRQChannelSubPriority         	= 3;        					// �����ȼ�
    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQͨ��ʹ��
    NVIC_Init(&nvic);   														// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���
    
	
//	/*���÷����жϣ���δʹ�ã�*/	
//    nvic.NVIC_IRQChannel                    	= CAN1_TX_IRQn;					// �����жϷ��������
//    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// ��ռ���ȼ�
//    nvic.NVIC_IRQChannelSubPriority         	= 2;        					// �����ȼ�
//    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQͨ��ʹ��
//    NVIC_Init(&nvic);   														// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���
 
 
	/*����CAN��ؼĴ���*/
    CAN_DeInit(CAN1);															// ����CAN�Ĵ���
    CAN_StructInit(&can1); 														// ΪCAN��ʼ���ṹ�帳��ʼֵ  
	/* CAN�����ƼĴ�������CAN_MCR��*/
    can1.CAN_TTCM = DISABLE;        											// ʱ�䴥��ͨ��ģʽ
    can1.CAN_ABOM = DISABLE;        											// �Զ������߹رչ���
    can1.CAN_AWUM = DISABLE;        											// �Զ�����ģʽ
    can1.CAN_NART = DISABLE;        											// ��ֹ�Զ��ط���
    can1.CAN_RFLM = DISABLE;        											// ����FIFO����ģʽ
    can1.CAN_TXFP = ENABLE;         											// ����FIFIO���ȼ�
	/* CANλʱ��Ĵ�����CAN_BTR��*/
    can1.CAN_Mode 								= CAN_Mode_Normal;				// ��ͨģʽ
    can1.CAN_SJW  								= CAN_SJW_1tq;    				// ����ͬ����Ծ���
    can1.CAN_BS1  								= CAN_BS1_9tq;    				// ʱ���1
    can1.CAN_BS2  								= CAN_BS2_4tq;    				// ʱ���2
    can1.CAN_Prescaler 							= 3;         					// ��Ƶϵ��
    CAN_Init(CAN1, &can1);          											// ����ָ���Ĳ�����ʼ��CAN�Ĵ���(CAN1������=42MHz/3/(9+4+1)=1MHz)
	/* CAN������ */
    can1_filter.CAN_FilterNumber         		= 0;                       		// ������0
    can1_filter.CAN_FilterMode          		= CAN_FilterMode_IdMask;   		// ��ʶ��������Ϊ����ģʽ
    can1_filter.CAN_FilterScale          		= CAN_FilterScale_32bit;   		// һ��32λ��ʶ��������
    can1_filter.CAN_FilterIdHigh         		= 0x0000;                  		// 32λ��ʶ���������ĸ�16λ
    can1_filter.CAN_FilterIdLow          		= 0x0000;                  		// 32λ��ʶ���������ĵ�16λ
    can1_filter.CAN_FilterMaskIdHigh     		= 0x0000;                  		// �����������16λ
    can1_filter.CAN_FilterMaskIdLow      		= 0x0000;                  		// �����������16λ
    can1_filter.CAN_FilterFIFOAssignment 		= CAN_Filter_FIFO0;        		// ������0������FIFO0
    can1_filter.CAN_FilterActivation     		= ENABLE;                  		// ���������
    CAN_FilterInit(&can1_filter);             									// ����ָ���Ĳ�����ʼ��CAN_Filter�Ĵ���
    
	
	/*CAN�ж�ʹ��*/
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  									// �����ж�:FIFO 0��Ϣ�����жϣ��൱�ڿ����жϣ�
//    CAN_ITConfig(CAN1, CAN_IT_TME,  ENABLE);  								// �����жϣ�����������ж� 
}





/** --------------------------------------------------------------------------
  * @brief  ��ʼ��CAN2
  
  * @note	����	��PB5(CAN2_RX);PB6(CAN2_TX)
			������	��1MHz
			���㹫ʽBaudRate = 42MHz/Prescaler*(1+BS1+BS2)
			CAN2������=42MHz/3/(9+4+1)=1MHz
 -------------------------------------------------------------------------- **/
void CAN2_Configuration(void)
{
	/*�����ʼ���ṹ��*/
    GPIO_InitTypeDef       gpio = {0};											// ����GPIO��ʼ���ṹ��
    NVIC_InitTypeDef       nvic = {0};											// �����ж����ȼ���ʼ���ṹ��
    CAN_InitTypeDef        can2 = {0};											// ����CAN��ʼ���ṹ��
    CAN_FilterInitTypeDef  can2_filter = {0};									// ����CAN��ID��������ʼ���ṹ��

	
	/*����ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   					// ʹ��PB�˿�ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);   					// ʹ��CAN1ʱ��,42MHz(����ʹ��CAN2ʱ��Ҫ��ʹ��CAN1��ʱ��)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,  ENABLE);   					// ʹ��CAN2ʱ��,42MHz

	
	/*���ö˿ڸ���*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);						// GPIO�ڶ˿ڸ���ΪCANͨ�Ŷ˿�
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);

	
	/*����GPIO*/
    gpio.GPIO_Pin   							= GPIO_Pin_5 | GPIO_Pin_6;		// ���ó�ʼ����CAN���ź�
    gpio.GPIO_Mode  							= GPIO_Mode_AF;					// �˿ڸ���ģʽ
    GPIO_Init(GPIOB, &gpio);													// ����ָ���Ĳ�����ʼ��GPIO�Ĵ���


	/*���ý����ж�*/
    nvic.NVIC_IRQChannel                    	= CAN2_RX0_IRQn;				// �����жϷ��������
    nvic.NVIC_IRQChannelPreemptionPriority  	= 0;        					// ��ռ���ȼ�
    nvic.NVIC_IRQChannelSubPriority         	= 4;        					// �����ȼ�
    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQͨ��ʹ��
    NVIC_Init(&nvic);   														// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���
    
	
//	/*���÷����жϣ���δʹ�ã�*/	
//    nvic.NVIC_IRQChannel                    	= CAN2_TX_IRQn;					// �����жϷ��������
//    nvic.NVIC_IRQChannelPreemptionPriority  	= 1;        					// ��ռ���ȼ�
//    nvic.NVIC_IRQChannelSubPriority         	= 6;        					// �����ȼ�
//    nvic.NVIC_IRQChannelCmd                 	= ENABLE;   					// IRQͨ��ʹ��
//    NVIC_Init(&nvic);   														// ����ָ���Ĳ�����ʼ��NVIC�Ĵ���
 
 
	/*����CAN��ؼĴ���*/
    CAN_DeInit(CAN2);															// ����CAN�Ĵ���
    CAN_StructInit(&can2); 														// ΪCAN��ʼ���ṹ�帳��ʼֵ  
	/* CAN�����ƼĴ�������CAN_MCR��*/
    can2.CAN_TTCM = DISABLE;        											// ʱ�䴥��ͨ��ģʽ
    can2.CAN_ABOM = DISABLE;        											// �Զ������߹رչ���
    can2.CAN_AWUM = DISABLE;        											// �Զ�����ģʽ
    can2.CAN_NART = DISABLE;        											// ��ֹ�Զ��ط���
    can2.CAN_RFLM = DISABLE;        											// ����FIFO����ģʽ
    can2.CAN_TXFP = ENABLE;         											// ����FIFIO���ȼ�
	/* CANλʱ��Ĵ�����CAN_BTR��*/
    can2.CAN_Mode 								= CAN_Mode_Normal;				// ��ͨģʽ
    can2.CAN_SJW  								= CAN_SJW_1tq;    				// ����ͬ����Ծ���
    can2.CAN_BS1  								= CAN_BS1_9tq;    				// ʱ���1
    can2.CAN_BS2  								= CAN_BS2_4tq;    				// ʱ���2
    can2.CAN_Prescaler 							= 3;         					// ��Ƶϵ��
    CAN_Init(CAN2, &can2);          											// ����ָ���Ĳ�����ʼ��CAN�Ĵ���(CAN2������=42MHz/3/(9+4+1)=1MHz)
	/* CAN������ */
    can2_filter.CAN_FilterNumber         		= 14;                       	// ������
    can2_filter.CAN_FilterMode          		= CAN_FilterMode_IdMask;   		// ��ʶ��������Ϊ����ģʽ
    can2_filter.CAN_FilterScale          		= CAN_FilterScale_32bit;   		// һ��32λ��ʶ��������
    can2_filter.CAN_FilterIdHigh         		= 0x0000;                  		// 32λ��ʶ���������ĸ�16λ
    can2_filter.CAN_FilterIdLow          		= 0x0000;                  		// 32λ��ʶ���������ĵ�16λ
    can2_filter.CAN_FilterMaskIdHigh     		= 0x0000;                  		// �����������16λ
    can2_filter.CAN_FilterMaskIdLow      		= 0x0000;                  		// �����������16λ
    can2_filter.CAN_FilterFIFOAssignment 		= CAN_Filter_FIFO0;        		// ������0������FIFO0
    can2_filter.CAN_FilterActivation     		= ENABLE;                  		// ���������
    CAN_FilterInit(&can2_filter);             									// ����ָ���Ĳ�����ʼ��CAN_Filter�Ĵ���
    
	
	/*CAN�ж�ʹ��*/
    CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);  									// �����ж�:FIFO 0��Ϣ�����жϣ������ڿ����жϣ�
//    CAN_ITConfig(CAN2, CAN_IT_TME,  ENABLE);  								// �����жϣ�����������ж� 
}


