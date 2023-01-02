#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H

/** ȫ�ֱ�־�ṹ�� */
typedef struct
{
	bool UP_RunFlag_Pre;		//ǰ��pitch����˶����
	bool UP_RunFlag;			//pitch����˶����
	bool UP_ShootFlag;			//��������˶����
	bool UP_FrictionFlag;		//Ħ��������
	bool UP_SniperFlag_Pre;		//ǰ��ʶ���־
	bool UP_SniperFlag;			//�Ӿ�ʶ��������

	bool DN_RunFlag_Pre;		//ǰ��pitch����˶����
	bool DN_RunFlag;			//pitch����˶����
	bool DN_ShootFlag;			//��������˶����
	bool DN_FrictionFlag;		//Ħ����������־
	bool DN_SniperFlag_Pre;		//ǰ��ʶ���־
	bool DN_SniperFlag;			//�Ӿ�ʶ��������

	bool CS_RunFlag;			//����������־
	bool CS_RunFlag_Pre;		//ǰ�ε���������־
	
	bool PT_UPFlag;				//����̨�յ���ͣ�籣����־
	bool PT_DNFlag;				//����̨�յ���ͣ�籣����־
	
	bool ResetFlag;				//��λ��־λ
	bool InitFlag;				//��ʼ���ɹ���־λ
	
} ST_FLAG;





/** ģ�����߱�־�ṹ�� */
typedef struct
{
	bool RSState;			//����ϵͳ����
	bool UPGimbalState;		//����̨�ƿ�����
	bool UPComputerState;	//����̨С��������
	bool DNGimbalState;		//����̨�ƿ�����
	bool DNComputerState;	//����̨С��������
	bool Can1State;			//CAN1ģ������
	bool Can2State;			//CAN2ģ������
	bool CapacitorState; 	//����ģ���쳣
} ST_ERROR;





/** ��̨���ݷ��ͽ��սṹ�� */
typedef __packed struct
{
	__packed struct
	{
		u8 		head[2];				//2
		float 	Send_Data1;				//4
		s16 	Send_Data2;				//2
		s16 	Send_Data3;				//2
		u8 		Flag_1;					//1
		u8 		Flag_2;					//1
		u8 		tail[2];				//2
	} Send;								//total: 12 

	__packed struct
	{
		u8 		head[2];				//2
		float 	Send_Data1;				//4
		float 	Send_Data2;				//4
		int 	Send_Data3;				//4
		u8 		Flag_1;					//1
		u8 		Flag_2;					//1
		u8 		tail[2];				//2
	} Receive;							//total: 18
} ST_IMU;




/** VOFA+��λ��������ݰ� */
typedef __packed struct
{
	float State_Data1; 
	float State_Data2;
	float State_Data3;  
	float State_Data4;   
	float State_Data5;   
	float State_Data6;   
	float State_Data7; 
	float State_Data8;
	float State_Data9;  
	float State_Data10;   

	
	u8 Tail1;
	u8 Tail2;
	u8 Tail3;
	u8 Tail4;
} ST_UART_DATA_VOFA;
#endif
