/*
 * user_AS_State.c
 *
 *  Created on: Apr 26, 2025
 *      Author: 24116
 */

#include "user_AS_State.h"

void TS_State_Detect(void)//驱动系统检测，通过检测安全回路状态完成
{
	if(HAL_GPIO_ReadPin(TS_DETECT_GPIO_Port, TS_DETECT_Pin)==GPIO_PIN_SET)//高电平，说明安全回路闭合，驱动系统激活
	{
		if(TS_State==0)
		{
			TS_State=1;
		}
	}
	else if(HAL_GPIO_ReadPin(TS_DETECT_GPIO_Port, TS_DETECT_Pin)==GPIO_PIN_RESET)////低电平，说明安全回路断开，驱动系统未激活
	{
		if(TS_State==1)
		{
			TS_State=0;
		}
	}
}

void ASMS_State_Detect(void)//检测ASMS是否闭合，无人回路是否导通
{

	if(HAL_GPIO_ReadPin(ASMS_DETECT_GPIO_Port, ASMS_DETECT_Pin)==GPIO_PIN_SET)//高电平，说明ASMS闭合，无人回路导通
	{


		   ASMS_State=1;


	}
	else ////低电平，说明ASMS打开，无人回路断开
	{

			ASMS_State=0;
	}

}

void EBS_State_Detect(void)//检测EBS是否可用
{
	qiya_compare();
    if(QIYA_State==QIYA_OK)
    {
    	EBS_Able_State=EBS_Enable;
    }
    else
    {
    	EBS_Able_State=EBS_Disable;
    }
}
void EBS_State_solve()//对EBS状态进行处理，控制EBS故障灯
{
	if(EBS_Able_State==EBS_Disable)//EBS_ERR
	{
		//点亮EBS故障灯
		//控制制动电机，完成冗余制动
	}
	else
	{
		//熄灭EBS故障灯
	}

}

void ASB_Detect(void)//ASB自检
{
	EBS_State_Detect();
	Brake_Motor_State_Detect();
	//测试制动电机
	if(EBS_Able_State==EBS_Enable&&Brake_Motor==1)
	{
		ASB_State=1;//ASB自检没问题
	}
	else
	{
		ASB_State=0;//ASB自检有问题
	}

}
void Brake_Motor_State_Detect(void)
{
	/*检测行车制动电机*/
}

void AS_State_Detect_Conv(void)
{
	/*先对车辆状态进行检测*/
	TS_State_Detect();
	ASMS_State_Detect();
	EBS_State_Detect();
	ASB_Detect();

	/*根据车辆状态判断、转变当前状态机状态*/
	if(AS_State==AS_OFF_Status)
	{
		AS_OFF_Judge_Conv();
	}
	else if(AS_State==Manual_Drv_Status)
	{
		Manual_Drv_Status_Judge_Conv();
	}
	else if(AS_State==AS_Ready_Status)
	{
		AS_Ready_Status_Judge_Conv();
	}
	else if(AS_State==AS_Driving_Status)
	{
		AS_Driving_Status_Judge_Conv();
	}
	else if(AS_State==AS_Emergency_Status)
	{
		AS_Emergency_Status_Judge_Conv();
	}
	else if(AS_State==AS_Finished_Status)
	{
		AS_Finished_Status_Judge_Conv();
	}


}

void AS_OFF_Judge_Conv()//AS_OFF状态下判断状态的转变
{
if(ASMS_State==1&&TS_State==1&&ASB_State==1&&Driving_Mode==1)
{
	/*转换到AS_Ready状态*/
	AS_State=AS_Ready_Status;
}

else if(ASMS_State==0&&EBS_Able_State==EBS_Disable&&TS_State==1&&Driving_Mode==2)
{
	/*转换到Manual_Driving状态*/
	AS_State=Manual_Drv_Status;
}
}

void Manual_Drv_Status_Judge_Conv()//Manual_Drv状态下判断状态的转变
{
if(TS_State==0)
{
	AS_State=AS_OFF_Status;
}
}

void AS_Ready_Status_Judge_Conv()//AS_Ready状态下判断状态的转变
{
if(Go_valid==1)//接收到5s延时后的Go信号
{
	Go_valid=0;
	AS_State=AS_Driving_Status;
}
}

void AS_Driving_Status_Judge_Conv()//AS_Driving状态下判断状态的转变
{
if(Task_Finished==1)
{
	AS_State=AS_Finished_Status;
}
}

void AS_Emergency_Status_Judge_Conv()//AS_Emergency状态下判断状态的转变
{
if(EBS_BEE_Status==1&&ASMS_State==0&&Brake_Release_Status==1)
{
	EBS_BEE_Status=0;
	AS_State=AS_OFF_Status;
}
}
void AS_Finished_Status_Judge_Conv()//AS_Finished状态下判断状态的转变
{
 if(RES_Status==1)
 {
	RES_Status=0;
	//触发紧急制动，再紧急制动中状态机转换为AS Emergency
 }
 else if(ASMS_State==0&&Brake_Release_Status==1)
 {
	 AS_State=AS_OFF_Status;
 }

}


void AS_State_Send(void)
{
	 switch(AS_State)
	 {
	 case Manual_Drv_Status:
		 CAN_Send_Manual_Drv_Status();
		 break;
	 case AS_OFF_Status:
		 CAN_Send_AS_OFF_Status();
	     break;
	 case AS_Ready_Status:
		 CAN_Send_AS_Ready_Status();
		 break;
	 case AS_Driving_Status:
		 CAN_Send_AS_Driving_Status();
		 break;
	 case AS_Finished_Status:
		 CAN_Send_AS_Finished_Status();
		 break;
	 case AS_Emergency_Status:
		 CAN_Send_AS_Emergency_Status();
		 break;

	 }
}

void AS_State_Solve(void)
{
	 switch(AS_State)
		 {
		 case Manual_Drv_Status:
			 CAN_Send_Manual_Drv_Status();
			 break;
		 case AS_OFF_Status:
			 CAN_Send_AS_OFF_Status();
		     break;
		 case AS_Ready_Status:
			 CAN_Send_AS_Ready_Status();
			 break;
		 case AS_Driving_Status:
			 CAN_Send_AS_Driving_Status();
			 break;
		 case AS_Finished_Status:
			 CAN_Send_AS_Finished_Status();
			 break;
		 case AS_Emergency_Status:
			 CAN_Send_AS_Emergency_Status();
			 break;

		 }
}

void AS_Off_Solve()
{
 ASSI_OFF();
}
void AS_Ready_Solve()
{
	ASSI_Yellow_Stable();
}
void AS_Driving_Solve()
{
	ASSI_Yellow_Blink();
}
void AS_Emergency_Solve()
{
	EBS_Trigger();

}
void AS_Finished_Solve()
{
	DCF_Activate();
	ASSI_Blue_Stable();
}
void Manu_Driving_Solve()
{

}
