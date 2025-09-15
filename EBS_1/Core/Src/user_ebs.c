/*
 * user_ebs.c
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */

#include "user_ebs.h"

void EBS_Trigger(void)
{

		DCF_Activate();
		ASSI_Blue_Blink();
        BEE_Activate();

}

void EBS_Error_Trigger(void)
{

		EBS_Error_LED_Activate();
		AS_State=AS_Emergency;

}

//安全回路急停检测的中断重写
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==JITING_Pin)
	{
		if(HAL_GPIO_ReadPin(JITING_GPIO_Port, JITING_Pin)==GPIO_PIN_RESET)//检测到低电平说明断开
		{
			 __HAL_GPIO_EXTI_CLEAR_IT(JITING_Pin);
		    AS_State=AS_Emergency;
		}
		else
		{
			 __HAL_GPIO_EXTI_CLEAR_IT(JITING_Pin);
			//JITING_State=1;
		}
	}
}

void EBS_Release(void)
{

}

void EBS_Able_Detect(void)
{

  if((QIYA_State==QIYA_OK)&&(YOUYA_State==YOUYA_OK)&&(Sensor_State==Sensor_OK))
  {
  EBS_Able_State=EBS_Enable;//EBS功能正常
  EBS_Error_LED_DeActivate();
  }
else
  {
	EBS_Able_State=EBS_Disable;//EBS失效
	EBS_Error_Trigger();
  }

}


