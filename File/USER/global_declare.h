#ifndef GLOBAL_DECLARE_H
#define GLOBAL_DECLARE_H

#include "os_types.h"
#include "ParamConfig.h"
#include "project_types.h"

#define TIME() TIM5->CNT					

/** DMAÊý¾ÝÁ÷ */
#define UART5_RX_STREAM        	DMA1_Stream0
#define USART3_RX_STREAM        DMA1_Stream1
#define UART4_RX_STREAM         DMA1_Stream2
#define USART3_TX_STREAM        DMA1_Stream3
#define UART4_TX_STREAM         DMA1_Stream4
#define USART2_RX_STREAM        DMA1_Stream5
#define USART2_TX_STREAM        DMA1_Stream6
#define UART5_TX_STREAM       	DMA1_Stream7
#define UART8_TX_STREAM         DMA1_Stream0
#define UART7_TX_STREAM         DMA1_Stream1
#define UART7_RX_STREAM         DMA1_Stream3
#define UART8_RX_STREAM         DMA1_Stream6
#define USART6_RX_STREAM        DMA2_Stream1
#define USART1_RX_STREAM        DMA2_Stream2
#define USART6_TX_STREAM        DMA2_Stream6
#define USART1_TX_STREAM        DMA2_Stream7

extern SYSTEM_MONITOR systemMonitor;
extern TESTBOX TestBox;
extern u8 UA3RxDMAbuf[UA3RxDMAbuf_LEN];
extern u8 UA4RxDMAbuf[UA4RxDMAbuf_LEN+10];
extern ST_UART_DATA_VOFA StateDataSendBuff;
extern ST_IMU GimbalDataBuff;
extern ST_ERROR	stError;
extern ST_FLAG stFlag;
#endif
