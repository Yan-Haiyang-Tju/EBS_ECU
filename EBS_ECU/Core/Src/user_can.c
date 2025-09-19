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
   // HAL_Delay(50);
   // HAL_UART_Transmit(&huart1, "CAN_ItMsg Succeed", 19, 10);

    //HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_header, rx_data);

   // HAL_UART_Transmit(&huart1, "CAN_ReadMsg Succeed", 19, 10);
    while (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
    {
if(rx_data[0]==0)
{
	HAL_UART_Transmit(&huart1, "CAN_GetMsg00 Succeed", 20, 10);
}
    if (rx_header.StdId == 0x101)
    {
    	HAL_UART_Transmit(&huart1, "CAN_GetMsg Succeed", 18, 10);
        if(rx_data[0]==30)//AS_Ready
        {
        	AS_State=AS_Ready;
        }
        if(rx_data[0]==31)//AS_Driving
        {
            AS_State=AS_Driving;
        }
        if(rx_data[0]==32)//AS_Finished
        {
        	AS_State=AS_Finished;
        }
        if(rx_data[0]==33)//AS_Emergency
        {
        	AS_State=AS_Emergency;
        }
        if(rx_data[0]==34)//AS_Off
        {
            AS_State=AS_Off;
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
    canFilter.FilterIdHigh = 0x101 << 5;     // ID左移5位对齐寄存器高位
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

void CAN_Send_AS_Emergency(void)
{
	CAN_SendMessage(CAN_AS_Emergency,0);
}
void CAN_Send_EBS_Disable(void)
{
	CAN_SendMessage(CAN_EBS_Disable,0);
}
