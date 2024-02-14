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

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;


uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal);

uint32_t adc_voltage_ph12();
uint32_t adc_voltage_ph13();
uint32_t adc_voltage_ph23();

uint32_t adc_current_ph1();
uint32_t adc_current_ph2();
uint32_t adc_current_ph3();

uint32_t adc_voltage_offset();
uint32_t adc_voltage_DClink();



#endif /* INC_ADC_HANDLER_H_ */
