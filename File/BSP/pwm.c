#include "pwm.h"



static u16 g_Rstnum8 = 0;


/********************************************************************
*@Func:	
		PWM部分初始化 （使用端口PB5输出）
******
*@para:
		PWM输出初始化
		mode 频率区间选择，0为Hz级（1Hz-1000Hz），1为KHZ级（1KHZ-1000KHZ)
		f 频率（Hz级与KHz级均为1-1000）
		duty 占空比(0-100]
******
*@desc:
		TIM8 PWM部分初始化
		高级定时器
		PWM频率计算公式（基于定时器溢出）：f = Tclk / ((rstnum+1)*(psc+1))
		系统频率1分频时（TIM_CKD_DIV1），Tclk = 168M
		使用端口PB5输出（可修改）
		占空比原理： 比较值 = 重载值 * 占空比(duty/100) , 当定时器计数值小于比较值时，输出低电平
******
*@example:	
		TIM8_PWM_Init(0,100);
******
*@info:	
		Autor:	王阳
		QQ: 	2844636987
		Phone:	18273423645
		update:	20220728
		
		注:		本函数只适用于stm32f4系列中主频为168Mhz的单片机
*********************************************************************/ 
void TIM8_PWM_Init(u8 mode, u16 f)
{  
	u16 rstnum = 65535;  	// 重载值
    u16 psc = 65535;		// 时钟的预分频数

	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	
	 // 频率区间选择
    if(mode == 0)
    {
        rstnum = 10000/f -1;
        psc = 16799;
        // 实际调节区间1/6Hz - 5000Hz  
    }
    else if(mode == 1)
    {
        rstnum = 1000/f -1;
        psc = 167;
        // 实际调节区间1/6KHz - 1000KHz
    }
	g_Rstnum8 = rstnum;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);				// 使能定时器2时钟
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  				// 使能GPIO外设和AFIO复用功能模块时钟

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 				// GPIOC8复用为定时器8

 
   //设置该引脚为复用输出功能,输出TIM8 CH3的PWM脉冲波形	GPIOC8
	GPIO_InitStructure.GPIO_Pin 	= 	GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_AF;  					// 复用推挽输出
	GPIO_InitStructure.GPIO_OType 	= 	GPIO_OType_PP;  				// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd	= 	GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);								// 初始化GPIO
 
   //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period 		= 	g_Rstnum8; 				// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=	psc; 					// 设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 	TIM_CKD_DIV1; 			// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= 	TIM_CounterMode_Up;		// TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 					// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM8 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode 			= 	TIM_OCMode_PWM1; 			// 选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState 	= 	TIM_OutputState_Enable; 	// 比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity 		= 	TIM_OCPolarity_High; 		// 输出极性:TIM输出比较极性高

	TIM_OC3Init(TIM8, &TIM_OCInitStructure);              					// 根据T指定的参数初始化外设TIM8 OC3
	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);          				// 使能TIM8在CCR2上的预装载寄存器
	
	TIM_Cmd(TIM8, ENABLE);  												// 使能TIM8
	TIM_ARRPreloadConfig(TIM8, ENABLE); 									// 使能TIMx在ARR上的预装载寄存器	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);        								// MOE 主输出使能,高级定时器必须开启这个


}




/*****************************************************************************
*@Func:	
		PWM通道设置占空比
******
*@para:	
		tnum为时钟源号码,duty为高电平占比,cnum为PWM通道号
******
*@desc:	
		占空比原理： 比较值 = 重载值 * 占空比(duty/100) , 
		当定时器计数值小于比较值时，输出低电平
******
*@example:	
		PWM_SetDuty(TIM8, 0.15, 3);
******
*@info:	
		Autor:	王阳
		QQ: 	2844636987
		Phone:	18273423645
		update:	20220728
		
		注:		本函数只适用于stm32f4系列单片机
******************************************************************************/ 
void PWM_SetDuty(TIM_TypeDef* tnum, float duty, u8 cnum)
{
	u16 			CompareValue = 0;  											// 比较值
	SetDutyFunc 	SetDuty;													// PWM通道的设置函数
	if(duty >= 0 && duty <= 1)
	{
		CompareValue = (u16)((g_Rstnum8 + 1) * duty);
		switch(cnum)															// 不同通道号的设置函数不同
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
