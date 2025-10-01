/*
 * user_ebs.h
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */

#ifndef INC_USER_EBS_H_
#define INC_USER_EBS_H_

#include "main.h"
extern uint8_t EBS_State;
extern uint8_t EBS_Error_State;
extern uint8_t JITING_State;
extern uint8_t EBS_Able_State;
extern uint8_t YOUYA_State;
extern uint8_t QIYA_State;
extern uint8_t Sensor_State;
extern uint8_t AS_State;
extern volatile uint8_t EBS_Trigger_Reason;
extern volatile uint8_t EBS_LOGIC_POWER_STATE;

extern volatile uint8_t EBS_Trigger_State;//0:EBS未触发 1:EBS触发状态
extern volatile uint8_t EBS_Test_State;//0:EBS未触发或触发未超过2s，不能进行释放检测 1:超过2s，可以进行释放检测

void EBS_State_Detect(void);
void EBS_Able_Detect(void);
void EBS_Trigger(void);
void Redundant_Driving_Brake_Trigger();
void AS_Finished_Trigger_EBS(void);//在AS_Finished状态下，因为任务完成、触发了紧急制动，并非因为出现紧急情况触发了紧急制动(所以不进入AS_Emergency状态)
void N_ERR_IND_UP(void);

#endif /* INC_USER_EBS_H_ */
