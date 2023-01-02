#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H

/** 全局标志结构体 */
typedef struct
{
	bool UP_RunFlag_Pre;		//前次pitch电机运动标记
	bool UP_RunFlag;			//pitch电机运动标记
	bool UP_ShootFlag;			//拨弹电机运动标记
	bool UP_FrictionFlag;		//摩擦轮启动
	bool UP_SniperFlag_Pre;		//前次识别标志
	bool UP_SniperFlag;			//视觉识别物体标记

	bool DN_RunFlag_Pre;		//前次pitch电机运动标记
	bool DN_RunFlag;			//pitch电机运动标记
	bool DN_ShootFlag;			//拨弹电机运动标记
	bool DN_FrictionFlag;		//摩擦轮启动标志
	bool DN_SniperFlag_Pre;		//前次识别标志
	bool DN_SniperFlag;			//视觉识别物体标记

	bool CS_RunFlag;			//底盘启动标志
	bool CS_RunFlag_Pre;		//前次底盘启动标志
	
	bool PT_UPFlag;				//上云台空弹仓停电保护标志
	bool PT_DNFlag;				//下云台空弹仓停电保护标志
	
	bool ResetFlag;				//复位标志位
	bool InitFlag;				//初始化成功标志位
	
} ST_FLAG;





/** 模块离线标志结构体 */
typedef struct
{
	bool RSState;			//裁判系统离线
	bool UPGimbalState;		//上云台云控离线
	bool UPComputerState;	//上云台小电脑离线
	bool DNGimbalState;		//下云台云控离线
	bool DNComputerState;	//下云台小电脑离线
	bool Can1State;			//CAN1模块离线
	bool Can2State;			//CAN2模块离线
	bool CapacitorState; 	//电容模块异常
} ST_ERROR;





/** 云台数据发送接收结构体 */
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




/** VOFA+上位机软件数据包 */
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
