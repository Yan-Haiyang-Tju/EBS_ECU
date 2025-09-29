/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BEE_JDQ_Pin|OUTPUT5_Pin|OUTPUT6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TS_JDQ_Pin|DCF_JDQ_Pin|OUTPUT1_Pin|WDOG_Pin
                          |AS_CLOSE_SDC_Pin|N_ERR_IND_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EBS_ERR_GPIO_Port, EBS_ERR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : BEE_JDQ_Pin OUTPUT5_Pin OUTPUT6_Pin */
  GPIO_InitStruct.Pin = BEE_JDQ_Pin|OUTPUT5_Pin|OUTPUT6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : TS_JDQ_Pin DCF_JDQ_Pin EBS_ERR_Pin OUTPUT1_Pin
                           WDOG_Pin AS_CLOSE_SDC_Pin N_ERR_IND_Pin */
  GPIO_InitStruct.Pin = TS_JDQ_Pin|DCF_JDQ_Pin|EBS_ERR_Pin|OUTPUT1_Pin
                          |WDOG_Pin|AS_CLOSE_SDC_Pin|N_ERR_IND_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TS_DETECT_Pin SHIFANGFA_DETECT_Pin EBS_LOGIC_POWER_DETECT_Pin INPUT5_Pin */
  GPIO_InitStruct.Pin = TS_DETECT_Pin|SHIFANGFA_DETECT_Pin|EBS_LOGIC_POWER_DETECT_Pin|INPUT5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ASMS_DETECT_Pin */
  GPIO_InitStruct.Pin = ASMS_DETECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ASMS_DETECT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : INPUT3_Pin INPUT4_Pin */
  GPIO_InitStruct.Pin = INPUT3_Pin|INPUT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
