#include "global_declare.h"



/** ϵͳ״̬ */
ST_FLAG 	stFlag = {FALSE};										// ȫ�ֱ�־λ
ST_ERROR 	stError = {FALSE};										// ģ���쳣��־λ
SYSTEM_MONITOR systemMonitor 		= {0};							// ϵͳ������

/** �������ݰ� */
TESTBOX TestBox;

/** DMA���ջ��� */
u8 UA3RxDMAbuf[UA3RxDMAbuf_LEN] = {0};								// ����3���ջ���
u8 UA4RxDMAbuf[UA4RxDMAbuf_LEN + 10] = {0};							// ����3���ջ���

ST_UART_DATA_VOFA StateDataSendBuff = {.Tail1 = 0x00, .Tail2 = 0x00, .Tail3 = 0x80, .Tail4 = 0x7F};		// ��λ���������ݰ�
ST_IMU GimbalDataBuff = {.Send.head[0] = 0x55, .Send.head[1] = 0x00};									// ��̨ͨ�����ݰ�
