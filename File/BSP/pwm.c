#include "pwm.h"



static u16 g_Rstnum8 = 0;


/********************************************************************
*@Func:	
		PWM���ֳ�ʼ�� ��ʹ�ö˿�PB5�����
******
*@para:
		PWM�����ʼ��
		mode Ƶ������ѡ��0ΪHz����1Hz-1000Hz����1ΪKHZ����1KHZ-1000KHZ)
		f Ƶ�ʣ�Hz����KHz����Ϊ1-1000��
		duty ռ�ձ�(0-100]
******
*@desc:
		TIM8 PWM���ֳ�ʼ��
		�߼���ʱ��
		PWMƵ�ʼ��㹫ʽ�����ڶ�ʱ���������f = Tclk / ((rstnum+1)*(psc+1))
		ϵͳƵ��1��Ƶʱ��TIM_CKD_DIV1����Tclk = 168M
		ʹ�ö˿�PB5��������޸ģ�
		ռ�ձ�ԭ�� �Ƚ�ֵ = ����ֵ * ռ�ձ�(duty/100) , ����ʱ������ֵС�ڱȽ�ֵʱ������͵�ƽ
******
*@example:	
		TIM8_PWM_Init(0,100);
******
*@info:	
		Autor:	����
		QQ: 	2844636987
		Phone:	18273423645
		update:	20220728
		
		ע:		������ֻ������stm32f4ϵ������ƵΪ168Mhz�ĵ�Ƭ��
*********************************************************************/ 
void TIM8_PWM_Init(u8 mode, u16 f)
{  
	u16 rstnum = 65535;  	// ����ֵ
    u16 psc = 65535;		// ʱ�ӵ�Ԥ��Ƶ��

	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	
	 // Ƶ������ѡ��
    if(mode == 0)
    {
        rstnum = 10000/f -1;
        psc = 16799;
        // ʵ�ʵ�������1/6Hz - 5000Hz  
    }
    else if(mode == 1)
    {
        rstnum = 1000/f -1;
        psc = 167;
        // ʵ�ʵ�������1/6KHz - 1000KHz
    }
	g_Rstnum8 = rstnum;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);				// ʹ�ܶ�ʱ��2ʱ��
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  				// ʹ��GPIO�����AFIO���ù���ģ��ʱ��

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 				// GPIOC8����Ϊ��ʱ��8

 
   //���ø�����Ϊ�����������,���TIM8 CH3��PWM���岨��	GPIOC8
	GPIO_InitStructure.GPIO_Pin 	= 	GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_AF;  					// �����������
	GPIO_InitStructure.GPIO_OType 	= 	GPIO_OType_PP;  				// �����������
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd	= 	GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);								// ��ʼ��GPIO
 
   //��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_Period 		= 	g_Rstnum8; 				// ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 	=	psc; 					// ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 	TIM_CKD_DIV1; 			// ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= 	TIM_CounterMode_Up;		// TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 					// ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM8 Channel3 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode 			= 	TIM_OCMode_PWM1; 			// ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState 	= 	TIM_OutputState_Enable; 	// �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity 		= 	TIM_OCPolarity_High; 		// �������:TIM����Ƚϼ��Ը�

	TIM_OC3Init(TIM8, &TIM_OCInitStructure);              					// ����Tָ���Ĳ�����ʼ������TIM8 OC3
	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);          				// ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  												// ʹ��TIM8
	TIM_ARRPreloadConfig(TIM8, ENABLE); 									// ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);        								// MOE �����ʹ��,�߼���ʱ�����뿪�����


}




/*****************************************************************************
*@Func:	
		PWMͨ������ռ�ձ�
******
*@para:	
		tnumΪʱ��Դ����,dutyΪ�ߵ�ƽռ��,cnumΪPWMͨ����
******
*@desc:	
		ռ�ձ�ԭ�� �Ƚ�ֵ = ����ֵ * ռ�ձ�(duty/100) , 
		����ʱ������ֵС�ڱȽ�ֵʱ������͵�ƽ
******
*@example:	
		PWM_SetDuty(TIM8, 0.15, 3);
******
*@info:	
		Autor:	����
		QQ: 	2844636987
		Phone:	18273423645
		update:	20220728
		
		ע:		������ֻ������stm32f4ϵ�е�Ƭ��
******************************************************************************/ 
void PWM_SetDuty(TIM_TypeDef* tnum, float duty, u8 cnum)
{
	u16 			CompareValue = 0;  											// �Ƚ�ֵ
	SetDutyFunc 	SetDuty;													// PWMͨ�������ú���
	if(duty >= 0 && duty <= 1)
	{
		CompareValue = (u16)((g_Rstnum8 + 1) * duty);
		switch(cnum)															// ��ͬͨ���ŵ����ú�����ͬ
		{
			case 1:
				SetDuty = TIM_SetCompare1;										
				break;
			case 2:
				SetDuty = TIM_SetCompare2;
				break;
			case 3:
				SetDuty = TIM_SetCompare3;
				break;
			case 4:
				SetDuty = TIM_SetCompare4;
				break;
			default:
				SetDuty = TIM_SetCompare1;
				break;
		}
		SetDuty(tnum, CompareValue);
	}
}
