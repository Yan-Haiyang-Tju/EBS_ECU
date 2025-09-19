/*
 * user_adc.h
 *
 *  Created on: Apr 21, 2025
 *      Author: 24116
 */

#ifndef INC_USER_ADC_H_
#define INC_USER_ADC_H_
#include <stdint.h>
#include "main.h"


extern uint16_t adc_value[4];
extern uint8_t YOUYA_State;
extern uint8_t QIYA_State;

uint32_t get_adc_value(void);
void qiya_compare(void);
void youya_compare(void);
void YOUYA_QIYA_Detect(void);

#endif /* INC_USER_ADC_H_ */
