/*
 * user_AS_State.h
 *
 *  Created on: Apr 26, 2025
 *      Author: 24116
 */

#ifndef INC_USER_AS_STATE_H_
#define INC_USER_AS_STATE_H_

#include "main.h"

extern uint8_t AS_State;

extern volatile uint8_t TS_State;//驱动系统状态
extern volatile uint8_t ASMS_State;//无人主开关状态
void AS_State_Detect(void);
void ASMS_State_Detect(void);
void TS_State_Detect(void);

#endif /* INC_USER_AS_STATE_H_ */
