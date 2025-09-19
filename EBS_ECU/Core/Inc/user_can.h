/*
 * user_can.h
 *
 *  Created on: Apr 20, 2025
 *      Author: 24116
 */

#ifndef INC_USER_CAN_H_
#define INC_USER_CAN_H_
#include "main.h"

extern uint8_t AS_State;
extern UART_HandleTypeDef huart1;

void CAN_Init();
void CAN_Filter0_Config(void);
void CAN_SendMessage(uint8_t Send_Id,uint16_t Value);
void CAN_Send_AS_Emergency(void);

#endif /* INC_USER_CAN_H_ */
