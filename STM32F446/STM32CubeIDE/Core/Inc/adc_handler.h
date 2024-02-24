/*
 * adc_handler.h
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

#ifndef INC_ADC_HANDLER_H_
#define INC_ADC_HANDLER_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*
 * used for using ADC handlers
 */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;


uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal);

uint32_t ADC_Uab();
uint32_t ADC_Uac();
uint32_t ADC_Ubc();

uint32_t ADC_Ia();
uint32_t ADC_Ib();
uint32_t ADC_Ic();

uint32_t ADC_Offset();
uint32_t ADC_DClink();



#endif /* INC_ADC_HANDLER_H_ */
