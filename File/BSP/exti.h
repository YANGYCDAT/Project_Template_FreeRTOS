#ifndef _EXTI_H_
#define _EXTI_H_
#include "main.h"

void PhotoGate_GPIO_Configuration(void);
//void EXTI_Configuration(void);
void EXTI1_Cmd(FunctionalState NewState);
void EXTI2_Cmd(FunctionalState NewState);
void EXTI3_Cmd(FunctionalState NewState);

#endif
