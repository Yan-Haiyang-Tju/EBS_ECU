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



void ASB_Detect(void)//ASB自检
{
	EBS_State_Detect();
	Brake_Motor_State_Detect();
	//测试制动电机
	if(EBS_Able_State==EBS_Enable&&Brake_Motor_State==1)
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
if(ASMS_State==1&&TS_State==1&&ASB_State==1&&Driving_Mode_From_ACU==2)
{
	/*转换到AS_Ready状态  进入AS_Ready前，把计数归零，GO_valid置否，开启GO计数*/
	GO_WAIT_num=0;//计数归零
	GO_Wait_State=0;//超过5s标志归零
	Go_valid=0;//GO_valid置否

	AS_State=AS_Ready_Status;//切换到AS_Ready状态

	if(GO_Wait_Count_State=0)//切换到AS_Ready就开启GO定时
	{
		GO_Wait_Count_State=1;//开启GO定时
	}

}

else if(ASMS_State==0&&EBS_Able_State==EBS_Disable&&TS_State==1&&Driving_Mode_From_ACU==1)
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
	if(EBS_Able_State==EBS_Disable)//EBS出现问题，切换至EBS_ERROR紧急制动
	{
		EBS_Trigger_Reason=1;//触发原因是EBS_ERR
		AS_State=AS_Emergency_Status;
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		GO_Wait_Count_State=0;//停止GO计数
		GO_WAIT_num=0;//GO计数清零
		GO_Wait_State=0;
	}
	else if(RES_Status==1)//触发了RES
	{
		RES_Status=0;
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		GO_Wait_Count_State=0;//停止GO计数
		GO_WAIT_num=0;//GO计数清零
		GO_Wait_State=0;
	}
	else if(TS_State==0)//安全回路断开，说明按下了急停
	{
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		GO_Wait_Count_State=0;//停止GO计数
		GO_WAIT_num=0;//GO计数清零
		GO_Wait_State=0;
	}
	else if(ASMS_State==0)//无人主开关打开，无人回路断开
	{
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		GO_Wait_Count_State=0;//停止GO计数
		GO_WAIT_num=0;//GO计数清零
		GO_Wait_State=0;
	}
	else//不进入AS_Emergency
	{
		if(Go_valid==1)//接收到5s延时后的Go信号
		{
			AS_State=AS_Driving_Status;
			Go_valid=0;
			GO_Wait_State=0;
			R2D_State=1;//切换到AS_Driving时，把R2D_State置1,开启R2D定时
			R2D_num=0;//切换到AS_Driving时，把R2D_num归零
		}
	}
}

void AS_Driving_Status_Judge_Conv()//AS_Driving状态下判断状态的转变
{
	if(EBS_Able_State==EBS_Disable)//EBS出现问题，切换至EBS_ERROR紧急制动
	{
	EBS_Trigger_Reason=1;//触发原因是EBS_ERR
	AS_State=AS_Emergency_Status;
	EBS_BEE_STATE=1;//EBS鸣笛报警状态
	BEE_enabled=2;//开启EBS鸣笛

	R2D_num=0;//R2D计时归零，防止意外
	R2D_State=0;//R2D_State置否
	}
	else if(RES_Status==1)//触发了RES
	{
		RES_Status=0;
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛


		R2D_num=0;//R2D计时归零，防止意外
		R2D_State=0;//R2D_State置否
	}
	else if(TS_State==0)//安全回路断开，说明按下了急停
	{
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		R2D_num=0;//R2D计时归零，防止意外
		R2D_State=0;//R2D_State置否
	}
	else if(ASMS_State==0)//无人主开关打开，无人回路断开
	{
		EBS_Trigger_Reason=0;//触发原因是正常触发
		AS_State=AS_Emergency_Status;//
		EBS_BEE_STATE=1;//EBS鸣笛报警状态
		BEE_enabled=2;//开启EBS鸣笛

		R2D_num=0;//R2D计时归零，防止意外
		R2D_State=0;//R2D_State置否
	}
	else
	{
		if(Task_Finished==1)//任务完成
		{
			AS_State=AS_Finished_Status;//转到AS_Finished状态
			R2D_num=0;//R2D计时归零，防止意外
			R2D_State=0;//R2D_State置否
			BEE_enabled=0;//关闭鸣笛
		}
	}
}

void AS_Emergency_Status_Judge_Conv()//AS_Emergency状态下判断状态的转变
{
if(EBS_BEE_STATE==0&&ASMS_State==0&&Brake_Release_Status==1)//EBS_BEE_STATE==0：EBS鸣笛结束
{

	AS_State=AS_OFF_Status;


}
}
void AS_Finished_Status_Judge_Conv()//AS_Finished状态下判断状态的转变
{
 if(RES_Status==1)//接收到了RES信号
 {
	RES_Status=0;
	AS_State=AS_Emergency_Status;//切换到紧急制动状态
	EBS_BEE_STATE=1;//EBS鸣笛报警状态
	BEE_enabled=2;//开启EBS鸣笛

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
			Manual_Drv_Status_Solve();
			 break;
		 case AS_OFF_Status:
			 AS_OFF_Status_Solve();
		     break;
		 case AS_Ready_Status:
			 AS_Ready_Status_Solve();
			 break;
		 case AS_Driving_Status:
			 AS_Driving_Status_Solve();
			 break;
		 case AS_Finished_Status:
			 AS_Finished_Status_Solve();
			 break;
		 case AS_Emergency_Status:
			 AS_Emergency_Status_Solve();
			 break;

		 }
}

void Manual_Drv_Status_Solve()
{
	ZHUANXIANG_Motor_Deactivate();
	Brake_Motor_Deactivate();
	ASSI_OFF();
}
void AS_OFF_Status_Solve()
{
	ZHUANXIANG_Motor_Deactivate();
	Brake_Motor_Deactivate();
	ASSI_OFF();
}

void AS_Ready_Status_Solve()
{

	ZHUANXIANG_Motor_Activate();
	Brake_Motor_Zhanyong();
	ASSI_Yellow_Stable();//黄灯常亮


}

void AS_Driving_Status_Solve()
{
	if(R2D_State==1)//处于R2D鸣笛状态，鸣笛
	{
		BEE_enabled=2;//BEE_enabled=2为R2D鸣笛
	}
	else if(R2D_State==0)//R2D鸣笛状态结束，不鸣笛
	{
		BEE_enabled=0;//0：关闭蜂鸣器 1：蜂鸣器EBS鸣笛 2：R2D鸣笛
	}

	Brake_Motor_Activate();
	ASSI_Yellow_Blink();

}
void AS_Finished_Status_Solve()
{
	EBS_Trigger();//断开安全回路，触发紧急制动
	ZHUANXIANG_Motor_Deactivate();//断开转向电机供电
	ASSI_Blue_Stable();//蓝灯常亮
}

void AS_Emergency_Status_Solve()
{

	if(EBS_BEE_STATE==0)//0:不报警
	{
			if(BEE_enabled!=0)
			{
				BEE_enabled=0;
			}
	}
	else if(EBS_BEE_STATE==1)//1:报警
	{
		if(BEE_enabled!=1)
		{
			BEE_enabled=1;//EBS鸣笛
		}
	}



	if(EBS_Trigger_Reason==0)//正常触发
	{
	EBS_Trigger();//断开安全回路，触发紧急制动
	ASSI_Blue_Blink();//蓝灯闪烁
	BEE_EBS();//EBS鸣笛
	}
	else if(EBS_Trigger_Reason==1)//因为EBS_ERR触发
	{
	/*相较于正常情况，需要激活EBS故障灯并进行冗余的行车制动*/
     EBS_Trigger();//断开安全回路，触发紧急制动
     Redundant_Driving_Brake_Trigger();//激活冗余的行车制动
     EBS_Error_LED_Activate();//激活EBS故障灯
     ASSI_Blue_Blink();//蓝灯闪烁
     BEE_EBS();//EBS鸣笛
	}
}



void Task_From_ACU_Solve(void)
{//在AS_OFF状态下处理域控传来的任务
	//AS_DRIVING_MODE 0:默认 1:手动驾驶任务 2：无人驾驶任务
	//默认状态将AS_Driving_Mode引脚置1，AS_CLOSE_SDC引脚置0
	//手动驾驶状态将AS_Driving_Mode引脚置0，AS_CLOSE_SDC引脚置0
	//无人驾驶状态将将AS_Driving_Mode引脚置1，AS_CLOSE_SDC引脚置1

	if(Driving_Mode_From_ACU==0)//默认状态
	{
		AS_DRIVING_MODE_UP();
		AS_CLOSE_SDC_DOWN();
	}
	else if(Driving_Mode_From_ACU==1)//手动驾驶任务
	{
		AS_DRIVING_MODE_DOWN();
		AS_CLOSE_SDC_DOWN();
	}
	else if(Driving_Mode_From_ACU==2)//无人驾驶任务
	{
		AS_DRIVING_MODE_UP();
		AS_CLOSE_SDC_UP();
	}
}
