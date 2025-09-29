/*
 * user_peripheral.h
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */

#ifndef INC_USER_PERIPHERAL_H_
#define INC_USER_PERIPHERAL_H_

#include "main.h"

void BEE_Activate(void);
void BEE_DeActivate(void);
void DCF_Activate(void);
void DCF_DeActivate(void);
void EBS_Error_LED_Activate(void);
void EBS_Error_LED_DeActivate(void);
void ASSI_Activate(void);
void ASSI_DeActivate(void);
void ZHUANXIANG_Motor_Activate(void);//转向电机使能
void ZHUANXIANG_Motor_Deactivate(void);//转向电机关闭
void Brake_Motor_Activate(void);//制动电机使能
void Brake_Motor_Zhanyong(void);//制动电机占用
void Brake_Motor_Deactivate(void);//制动电机关闭


#endif /* INC_USER_PERIPHERAL_H_ */
