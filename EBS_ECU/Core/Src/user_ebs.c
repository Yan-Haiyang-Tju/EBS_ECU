/*
 * user_ebs.c
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */

#include "user_ebs.h"

void EBS_Trigger(void)
{

	N_ERR_IND_DOWN();//拉低，断开安全回路，自动触发EBS

}



void EBS_LOGIC_Power_Detect()
{
	if(HAL_GPIO_ReadPin(EBS_LOGIC_POWER_DETECT_GPIO_Port, EBS_LOGIC_POWER_DETECT_Pin)==GPIO_PIN_SET)//有电
	{
		EBS_LOGIC_POWER_STATE=1;
	}
	else
	{
		EBS_LOGIC_POWER_STATE=0;
	}
}

void EBS_State_Detect(void)//检测EBS是否可用
{
	qiya_compare();
	EBS_LOGIC_Power_Detect();
    if(QIYA_State==QIYA_OK&&EBS_LOGIC_POWER_STATE==1) //气压没问题并且EBS有电并且油路
    {
    	EBS_Able_State=EBS_Enable;//EBS正常
    	EBS_Error_LED_DeActivate();//熄灭EBS故障灯
    }
    else
    {
    	/*检测到EBS出现问题，并点亮EBS故障灯*/
    	EBS_Able_State=EBS_Disable;//EBS系统出现问题
    	EBS_Error_LED_Activate();//点亮EBS故障灯
    }
}

void EBS_Release(void)
{

}




/*冗余的行车制动*/
void Redundant_Driving_Brake_Trigger()
{

}



/******与EBS逻辑电路的交互*******/

void AS_DRIVING_MODE_UP(void)
{
	HAL_GPIO_WritePin(AS_DRIVING_MODE_GPIO_Port, AS_DRIVING_MODE_Pin,GPIO_PIN_SET);//AS_DRIVING_MODE拉高
}

void AS_DRIVING_MODE_DOWN  (void)
{
	HAL_GPIO_WritePin(AS_DRIVING_MODE_GPIO_Port,AS_DRIVING_MODE_Pin,GPIO_PIN_RESET);//AS_DRIVING_MODE拉低
}

void AS_CLOSE_SDC_UP(void)
{
	HAL_GPIO_WritePin(AS_CLOSE_SDC_GPIO_Port, AS_CLOSE_SDC_Pin,GPIO_PIN_SET);//AS_CLOSE_SDC拉高
}

void AS_CLOSE_SDC_DOWN(void)
{
	HAL_GPIO_WritePin(AS_CLOSE_SDC_GPIO_Port, AS_CLOSE_SDC_Pin,GPIO_PIN_RESET);//AS_CLOSE_SDC拉低
}

void N_ERR_IND_UP(void)
{
	HAL_GPIO_WritePin(N_ERR_IND_GPIO_Port, N_ERR_IND_Pin,GPIO_PIN_SET);//N_ERR_IND拉高
}

void N_ERR_IND_DOWN(void)
{
	HAL_GPIO_WritePin(N_ERR_IND_GPIO_Port,  N_ERR_IND_Pin,GPIO_PIN_RESET);//N_ERR_IND拉低
}



