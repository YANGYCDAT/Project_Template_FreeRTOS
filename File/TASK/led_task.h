#ifndef LED_TASK_H
#define LED_TASK_H

#include "stm32f4xx_rcc.h"
#include "global_declare.h"
#include "project_types.h"


#define  LED_PINK_ON()      	GPIO_ResetBits(GPIOE, GPIO_Pin_15)
#define  LED_PINK_OFF()     	GPIO_SetBits(GPIOE, GPIO_Pin_15)
#define  LED_PINK_TOGGLE()  	GPIO_ToggleBits(GPIOE, GPIO_Pin_15)

#define  LED_BLUE_ON()      	GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define  LED_BLUE_OFF()     	GPIO_SetBits(GPIOE, GPIO_Pin_14)
#define  LED_BLUE_TOGGLE()  	GPIO_ToggleBits(GPIOE, GPIO_Pin_14)

#define  LED_GREEN_ON()      	GPIO_ResetBits(GPIOE, GPIO_Pin_13)
#define  LED_GREEN_OFF()     	GPIO_SetBits(GPIOE, GPIO_Pin_13)
#define  LED_GREEN_TOGGLE()  	GPIO_ToggleBits(GPIOE, GPIO_Pin_13)

#define  LED_RED_ON()      		GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define  LED_RED_OFF()     		GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define  LED_RED_TOGGLE()  		GPIO_ToggleBits(GPIOE, GPIO_Pin_12)

#define  LED_ORANGE_ON()      	GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define  LED_ORANGE_OFF()     	GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define  LED_ORANGE_TOGGLE()  	GPIO_ToggleBits(GPIOE, GPIO_Pin_11)

void LEDStateChange(void);

#endif
