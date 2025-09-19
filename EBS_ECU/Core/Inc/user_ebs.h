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

void EBS_Able_Detect(void);
#endif /* INC_USER_EBS_H_ */
