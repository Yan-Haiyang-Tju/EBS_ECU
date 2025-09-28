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

/*发送制动传感器数据*/
void CAN_Send_Brake_Sensor_Values(uint8_t Sensor_Type,uint16_t Sensor_Value);

/*AS状态发送*/
void CAN_Send_Manual_Drv_Status(void);
void CAN_Send_AS_OFF_Status(void);
void CAN_Send_AS_Ready_Status(void);
void CAN_Send_AS_Driving_Status(void);
void CAN_Send_AS_Finished_Status(void);
void CAN_Send_AS_Emergency_Status(void);
void CAN_Send_EBS_ERR_Status(void);



#endif /* INC_USER_CAN_H_ */
