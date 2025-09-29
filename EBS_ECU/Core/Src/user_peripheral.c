/*
 * user_peripheral.c
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */
#include "user_peripheral.h"
//蜂鸣器控制
void BEE_Activate(void)
{
	if(HAL_GPIO_ReadPin(BEE_JDQ_GPIO_Port, BEE_JDQ_Pin)==GPIO_PIN_RESET)
	{
		HAL_GPIO_WritePin(BEE_JDQ_GPIO_Port, BEE_JDQ_Pin, GPIO_PIN_SET);
	}
}

void BEE_DeActivate(void)
{
	if(HAL_GPIO_ReadPin(BEE_JDQ_GPIO_Port, BEE_JDQ_Pin)==GPIO_PIN_SET)
	{
		HAL_GPIO_WritePin(BEE_JDQ_GPIO_Port, BEE_JDQ_Pin, GPIO_PIN_RESET);
	}
}



void BEE_GO()
{

}

void BEE_EBS()
{

}

//电磁阀控制
void DCF_Activate(void)
{
	if(HAL_GPIO_ReadPin(DCF_JDQ_GPIO_Port, DCF_JDQ_Pin)==GPIO_PIN_RESET)
	{
		HAL_GPIO_WritePin(DCF_JDQ_GPIO_Port, DCF_JDQ_Pin, GPIO_PIN_SET);
	}
}

void DCF_DeActivate(void)
{
	if(HAL_GPIO_ReadPin(DCF_JDQ_GPIO_Port, DCF_JDQ_Pin)==GPIO_PIN_SET)
	{
		HAL_GPIO_WritePin(DCF_JDQ_GPIO_Port, DCF_JDQ_Pin, GPIO_PIN_RESET);
	}
}

//EBS故障灯
void EBS_Error_LED_Activate(void)
{

		HAL_GPIO_WritePin(EBS_ERR_GPIO_Port, EBS_ERR_Pin, GPIO_PIN_RESET);

}
void EBS_Error_LED_DeActivate(void)
{

		HAL_GPIO_WritePin(EBS_ERR_GPIO_Port, EBS_ERR_Pin, GPIO_PIN_SET);

}

void ZHUANXIANG_Motor_Activate(void)//转向电机激活
{

}
void ZHUANXIANG_Motor_Deactivate(void)//转向电机关闭
{

}

void Brake_Motor_Activate(void)//制动电机激活
{

}

void Brake_Motor_Zhanyong(void)//制动电机占用
{
	Brake_Motor_Activate();//首先激活制动电机
	//给一定制动压力，确保赛车在15%坡度上不发生滚动
}
void Brake_Motor_Deactivate(void)//制动电机关闭
{

}

//无人系统指示灯激活  ？？
/*
void ASSI_Activate(void)
{
	if(HAL_GPIO_ReadPin(ASLED_PWR_GPIO_Port, ASLED_PWR_Pin)==GPIO_PIN_RESET)
	{
		HAL_GPIO_WritePin(ASLED_PWR_GPIO_Port, ASLED_PWR_Pin, GPIO_PIN_SET);
	}
}

void ASSI_DeActivate(void)
{
	if(HAL_GPIO_ReadPin(ASLED_PWR_GPIO_Port, ASLED_PWR_Pin)==GPIO_PIN_SET)
	{
		HAL_GPIO_WritePin(ASLED_PWR_GPIO_Port, ASLED_PWR_Pin, GPIO_PIN_RESET);
	}
}
*/

