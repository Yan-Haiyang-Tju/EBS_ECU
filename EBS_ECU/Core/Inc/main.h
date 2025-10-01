/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "gpio.h"
#include "tim.h"
#include "user_can.h"
#include "user_adc.h"
#include "user_peripheral.h"
#include "user_rgb.h"
#include "adc.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BEE_JDQ_Pin GPIO_PIN_13
#define BEE_JDQ_GPIO_Port GPIOC
#define OUTPUT5_Pin GPIO_PIN_14
#define OUTPUT5_GPIO_Port GPIOC
#define OUTPUT6_Pin GPIO_PIN_15
#define OUTPUT6_GPIO_Port GPIOC
#define QIYA_ADC_Pin GPIO_PIN_2
#define QIYA_ADC_GPIO_Port GPIOA
#define YOUYA_ADC_Pin GPIO_PIN_3
#define YOUYA_ADC_GPIO_Port GPIOA
#define PWM_SERVO_BRAKE_Pin GPIO_PIN_6
#define PWM_SERVO_BRAKE_GPIO_Port GPIOA
#define PWM_STBY_Pin GPIO_PIN_7
#define PWM_STBY_GPIO_Port GPIOA
#define TS_JDQ_Pin GPIO_PIN_0
#define TS_JDQ_GPIO_Port GPIOB
#define DCF_JDQ_Pin GPIO_PIN_1
#define DCF_JDQ_GPIO_Port GPIOB
#define EBS_ERR_Pin GPIO_PIN_11
#define EBS_ERR_GPIO_Port GPIOB
#define TS_DETECT_Pin GPIO_PIN_12
#define TS_DETECT_GPIO_Port GPIOB
#define ASMS_DETECT_Pin GPIO_PIN_13
#define ASMS_DETECT_GPIO_Port GPIOB
#define SHIFANGFA_DETECT_Pin GPIO_PIN_14
#define SHIFANGFA_DETECT_GPIO_Port GPIOB
#define EBS_LOGIC_POWER_DETECT_Pin GPIO_PIN_15
#define EBS_LOGIC_POWER_DETECT_GPIO_Port GPIOB
#define AS_DRIVING_MODE_Pin GPIO_PIN_8
#define AS_DRIVING_MODE_GPIO_Port GPIOA
#define INPUT4_Pin GPIO_PIN_15
#define INPUT4_GPIO_Port GPIOA
#define INPUT5_Pin GPIO_PIN_3
#define INPUT5_GPIO_Port GPIOB
#define YULIUJDQ_Pin GPIO_PIN_4
#define YULIUJDQ_GPIO_Port GPIOB
#define WDOG_Pin GPIO_PIN_5
#define WDOG_GPIO_Port GPIOB
#define ASSI_PWM_Pin GPIO_PIN_6
#define ASSI_PWM_GPIO_Port GPIOB
#define AS_CLOSE_SDC_Pin GPIO_PIN_8
#define AS_CLOSE_SDC_GPIO_Port GPIOB
#define N_ERR_IND_Pin GPIO_PIN_9
#define N_ERR_IND_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define Manual_Drv_Status 1
#define AS_OFF_Status 2
#define AS_Ready_Status 3
#define AS_Driving_Status 4
#define AS_Finished_Status 5
#define AS_Emergency_Status 6
#define EBS_ERR_Status 7

#define Sensor_Error 0
#define Sensor_OK 1

#define YOUYA_Error 0
#define YOUYA_OK 1

#define QIYA_Error 0
#define QIYA_OK 1

#define EBS_Disable 0
#define EBS_Enable 1


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
