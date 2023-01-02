#ifndef __PWM_H
#define __PWM_H
#include "stm32f4xx.h"


typedef void (*SetDutyFunc)(TIM_TypeDef*, uint32_t);


extern u16 T8_rstnum;


void TIM8_PWM_Init(u8 mode, u16 f);
void PWM_SetDuty(TIM_TypeDef * tnum,float duty, u8 cnum);



#endif
