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

}

void ASB_Detect(void)//ASB自检
{


}

void AS_State_Detect(void)
{
	TS_State_Detect();//先对车辆状态进行检测
	ASMS_State_Detect();
	EBS_State_Detect();
	ASB_Detect();

	/*根据车辆状态判断当前状态机状态*/

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
	 case EBS_ERR_Status:
		 CAN_Send_EBS_ERR_Status();
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
		 case EBS_ERR_Status:
			 CAN_Send_EBS_ERR_Status();
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
