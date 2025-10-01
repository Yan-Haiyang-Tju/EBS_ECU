/*
 * user_can.c
 *
 *  Created on: Apr 20, 2025
 *      Author: 24116
 */

#include "user_can.h"
#include "stm32f1xx_hal_can.h"

const uint8_t CAN_AS_Emergency=20;
const uint8_t CAN_EBS_Disable=21;

const uint8_t CAN_EBS_Send_ID=0x51;
const uint8_t ACU_To_EBS_ID=0x50;
const uint8_t RES_ID=0x53;
/**** 状态机对应的数据 ****/
const uint8_t CAN_Manual_Drv_Status=0x01;
const uint8_t CAN_AS_OFF_Status=0x02;
const uint8_t CAN_AS_Ready_Status=0x03;
const uint8_t CAN_AS_Driving_Status=0x04;
const uint8_t CAN_AS_Finished_Status=0x05;
const uint8_t CAN_AS_Emergency_Status=0x06;
const uint8_t CAN_EBS_ERR_Status=0x07;

void CAN_Init()
{
	CAN_Filter0_Config();
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

//FIFO0回调重写
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    can_intterupt++;
    if(can_intterupt>=50)
    {
    	can_intterupt=0;
    }
   // HAL_Delay(50);
   // HAL_UART_Transmit(&huart1, "CAN_ItMsg Succeed", 19, 10);

    //HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_header, rx_data);

   // HAL_UART_Transmit(&huart1, "CAN_ReadMsg Succeed", 19, 10);
    while (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
    {

    if(rx_header.StdId == RES_ID)//消息从RES发来
    {
       if(GO_Wait_State==1)//超过5s
       {
    	   if(rx_data[0]==0x01)//判断消息内容
    	   {
    		   Go_valid=1;//5s后接收到了GO信号
    	   }
       }
       if(AS_State==AS_Ready_Status||AS_State==AS_Driving_Status||AS_State==AS_Finished_Status)
       {
    	   if(rx_data[1]==0x01)//RES急停信号 只有在AS_Ready或者AS_Driving或者AS_Finished状态才能转变，并且只有这几种状态才根据RES信号进行状态转变
    	   {
    	   RES_Status=1;
    	   }
       }
       if(rx_data[1]==0x02)//RES正常信号
       {
    	   RES_Status=0;
       }
    }
    if (rx_header.StdId == ACU_To_EBS_ID)//CAN消息由域控传来
    {
    	//HAL_UART_Transmit(&huart1, "CAN_GetMsg Succeed", 18, 10);
        if(rx_data[0]==0x01)//雷达、相机、惯导状态
        {
        	if(rx_data[1]==0x01)
        	{
        		LIDAR_Cam_MPU_State=0;
        		//存在传感器掉线
        	}
        	else if(rx_data[1]==0x02)
        	{
        		LIDAR_Cam_MPU_State=1;
        		//三个传感器都没问题
        	}
        	else
        	{
        		//此处CAN通信出现数据错误
        	}
        }
        else if(rx_data[0]==0x02)//域控发来的指令
        {
           if(rx_data[1]==0x01)//任务完成，进入AS_Finished状态
           {
        	   Task_Finished=1;
           }
           else if(rx_data[1]==0x02)//请求直接触发EBS
           {
        	   if(rx_data[2]==0x02)
        	   {
        		   //校验，确认触发EBS
        	   }
        	   else
        	   {
        		   //此处CAN通信出现错误
        	   }
           }
           else if(rx_data[1]==0x03)
           {

        	   //手动驾驶模式选择
        	   if(AS_State==AS_OFF_Status)//处于AS_OFF才可选择
        	   {
        	   Driving_Mode_From_ACU=1;
        	   }
           }
           else if(rx_data[1]==0x04)
           {
        	   //无人驾驶模式选择
        	   if(AS_State==AS_OFF_Status)//处于AS_OFF才可选择
        	   {
        	   Driving_Mode_From_ACU=2;
        	   }
        	   }
           else
           {
        	   //此处CAN通信出现错误
           }
        }
        else
        {
        	//此处CAN通信出现问题
        }


    }
    }
    //CAN_SendBack(rx_data);
    // 重新激活中断
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}


void CAN_Filter0_Config(void) {
    CAN_FilterTypeDef canFilter;

    // 基本参数
    canFilter.FilterBank = 0;               // 使用过滤器组0
    canFilter.FilterMode = CAN_FILTERMODE_IDMASK;   // 屏蔽位模式
    canFilter.FilterScale = CAN_FILTERSCALE_32BIT;  // 32位精度
    canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0; // 数据存入FIFO0
    canFilter.FilterActivation = ENABLE;     // 启用过滤器

    // ID与掩码计算（标准帧ID=0x101）
    canFilter.FilterIdHigh = ACU_To_EBS_ID << 5;     // ID左移5位对齐寄存器高位
    canFilter.FilterIdLow = 0x0000;          // 低16位未使用
    canFilter.FilterMaskIdHigh = 0x7FF << 5; // 掩码高11位全匹配（0x7FF=11位全1）  即屏蔽码
    canFilter.FilterMaskIdLow = 0x0006;      // 强制IDE=0（标准帧）+ RTR=0（数据帧）

    // 应用配置
    HAL_CAN_ConfigFilter(&hcan, &canFilter);
}

void CAN_SendBack(uint8_t Sendback[])//返回接受的数据，说明接收成功
{
	    CAN_TxHeaderTypeDef TxHeader;

	    uint32_t TxMailbox;
	    TxHeader.StdId = 0x101;      // 标准CAN ID
	    TxHeader.RTR = CAN_RTR_DATA; 		// 数据帧
	    TxHeader.IDE = CAN_ID_STD;   		// 使用标准ID
	    TxHeader.DLC = 8;            		// 数据长度码，表示8字节数据
	    TxHeader.TransmitGlobalTime = DISABLE;
	    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, Sendback, &TxMailbox) != HAL_OK)
	        {
	            // 发送失败处理
	        }
}

void CAN_SendMessage(uint8_t Send_Id,uint16_t Value){

    CAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8];
    uint32_t TxMailbox;
    TxHeader.StdId = 0x101;      // 标准CAN ID
    TxHeader.RTR = CAN_RTR_DATA; 		// 数据帧
    TxHeader.IDE = CAN_ID_STD;   		// 使用标准ID
    TxHeader.DLC = 8;            		// 数据长度码，表示8字节数据
    TxHeader.TransmitGlobalTime = DISABLE;

    TxData[0] = Send_Id;
    TxData[1] = (Value >> 8);
    TxData[2] = (Value & 0xFF);
    TxData[3] = 0x00;
    TxData[4] = 0x00;
    TxData[5] = 0x00;
    TxData[6] = 0x00;
    TxData[7] = 0x00;
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
    	 HAL_UART_Transmit(&huart1, "CAN_Send Error", 14, 10);
    	// HAL_Delay(50);
    	//ASSI_Yellow_Blink();
    }
    else
    {
    	// HAL_Delay(50);
    	 HAL_UART_Transmit(&huart1, "CAN_Send Succeed", 16, 10);

    }
}

void CAN_Send_AS_Status(uint8_t AS_Status){

    CAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8];
    uint32_t TxMailbox;
    TxHeader.StdId = CAN_EBS_Send_ID;      //EBS发送CAN_ID
    TxHeader.RTR = CAN_RTR_DATA; 		// 数据帧
    TxHeader.IDE = CAN_ID_STD;   		// 使用标准ID
    TxHeader.DLC = 8;            		// 数据长度码，表示8字节数据
    TxHeader.TransmitGlobalTime = DISABLE;

    TxData[0] = 0x01;
    TxData[1] = AS_Status;
    TxData[2] = 0x00;
    TxData[3] = 0x00;
    TxData[4] = 0x00;
    TxData[5] = 0x00;
    TxData[6] = 0x00;
    TxData[7] = 0x00;
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
    	 HAL_UART_Transmit(&huart1, "CAN_Send Error", 14, 10);
    	// HAL_Delay(50);
    	//ASSI_Yellow_Blink();
    }
    else
    {
    	// HAL_Delay(50);
    	 HAL_UART_Transmit(&huart1, "CAN_Send Succeed", 16, 10);

    }
}

void CAN_Send_Brake_Sensor_Values(uint8_t Sensor_Type,uint16_t Sensor_Value){

    CAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8];
    uint32_t TxMailbox;
    TxHeader.StdId = CAN_EBS_Send_ID;      //EBS发送CAN_ID
    TxHeader.RTR = CAN_RTR_DATA; 		// 数据帧
    TxHeader.IDE = CAN_ID_STD;   		// 使用标准ID
    TxHeader.DLC = 8;            		// 数据长度码，表示8字节数据
    TxHeader.TransmitGlobalTime = DISABLE;

    TxData[0] = 0x02;
    TxData[1] = Sensor_Type;
    TxData[2] = (Sensor_Value>>8);//高八位
    TxData[3] = (Sensor_Value&0xFF);//低八位
    TxData[4] = 0x00;
    TxData[5] = 0x00;
    TxData[6] = 0x00;
    TxData[7] = 0x00;
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
    	 HAL_UART_Transmit(&huart1, "CAN_Send Error", 14, 10);
    	// HAL_Delay(50);
    	//ASSI_Yellow_Blink();
    }
    else
    {
    	// HAL_Delay(50);
    	 HAL_UART_Transmit(&huart1, "CAN_Send Succeed", 16, 10);

    }
}

/****发送状态机状态*****/
void CAN_Send_Manual_Drv_Status(void)
{
	CAN_Send_AS_Status(CAN_Manual_Drv_Status);
}
void CAN_Send_AS_OFF_Status(void)
{
	CAN_Send_AS_Status(CAN_AS_OFF_Status);
}
void CAN_Send_AS_Ready_Status(void)
{
	CAN_Send_AS_Status(CAN_AS_Ready_Status);
}
void CAN_Send_AS_Driving_Status(void)
{
	CAN_Send_AS_Status(CAN_AS_Driving_Status);
}
void CAN_Send_AS_Finished_Status(void)
{
	CAN_Send_AS_Status(CAN_AS_Finished_Status);
}
void CAN_Send_AS_Emergency_Status(void)
{
	CAN_Send_AS_Status(CAN_AS_Emergency_Status);
}
void CAN_Send_EBS_ERR_Status(void)
{
	CAN_Send_AS_Status(CAN_EBS_ERR_Status);
}
/****    ****/




void CAN_Send_AS_Emergency(void)
{
	CAN_SendMessage(CAN_AS_Emergency,0);
}
void CAN_Send_EBS_Disable(void)
{
	CAN_SendMessage(CAN_EBS_Disable,0);
}



