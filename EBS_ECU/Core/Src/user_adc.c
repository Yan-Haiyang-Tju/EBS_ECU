/*
 * user_ADC.c
 *
 *  Created on: Apr 21, 2025
 *      Author: 24116
 */

#include "user_adc.h"
#include <stdint.h>
uint32_t get_adc_value(void)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1);
    return HAL_ADC_GetValue(&hadc1);

}

void qiya_compare(void)
{
	 if(adc_value[1]<500||adc_value[1]>3000)
	 {
		 QIYA_State=QIYA_Error;
	 }
	 else
	 {
		 QIYA_State=QIYA_OK;
	 }

}

void youya_compare(void)
{
	if(adc_value[2]<500||adc_value[2]>3000)
		 {
			 YOUYA_State=YOUYA_Error;
		 }
		 else
		 {
			 YOUYA_State=YOUYA_OK;
		 }
}
void YOUYA_QIYA_Detect(void)
{
	 for(int i=0;i<4;i++)
		  {
			  adc_value[i]=get_adc_value();
		  }
	 qiya_compare();
	 youya_compare();


}
