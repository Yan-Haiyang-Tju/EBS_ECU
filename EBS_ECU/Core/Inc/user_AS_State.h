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

extern volatile uint8_t Driving_Mode_From_ACU;//域控发来的驾驶模式指令0:默认 1:手动驾驶任务 2：无人驾驶任务
extern volatile uint8_t ASB_State;//ASB状态
extern volatile uint8_t TS_State;//驱动系统状态
extern volatile uint8_t ASMS_State;//无人主开关状态
extern volatile uint8_t Go_valid;//0:没有接收到Go信号 1:进入AS_Ready5s后接收到Go信号
extern volatile uint8_t Task_Finished;//0:默认状态 1:接收到域控传来的任务完成消息
extern volatile uint8_t EBS_BEE_Status;//0:默认状态 1:EBS鸣笛结束
extern volatile uint8_t Brake_Release_Status;//0:制动未释放 1:制动释放(根据气压、油压)
extern volatile uint8_t RES_Status;//0:未触发RES 1:触发RES (来自CAN总线的RES接收端消息)
extern volatile uint8_t Brake_Motor_State;//0:制动电机有问题 1:制动电机没问题
extern volatile uint8_t EBS_Trigger_Reason;//0:正常触发 1:因为EBS_ERR触发
extern volatile uint8_t GO_Wait_Count_State;//是否开始GO计数 0:关闭GO计时 1:开始GO计时
extern volatile uint8_t GO_Wait_State;//0:未超过5s 1：超过5s
extern volatile uint8_t R2D_State;//R2D状态
extern volatile uint8_t EBS_BEE_STATE;//0:EBS不报警 1:EBS报警

extern uint8_t EBS_Able_State;

void AS_State_Detect(void);
void ASMS_State_Detect(void);
void TS_State_Detect(void);

#endif /* INC_USER_AS_STATE_H_ */
