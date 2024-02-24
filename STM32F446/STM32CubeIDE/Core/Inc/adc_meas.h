/*
 * adc_meas.h
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

#ifndef INC_ADC_MEAS_H_
#define INC_ADC_MEAS_H_

/* Includes ------------------------------------------------------------------*/
#include "adc_handler.h"
#include "filter.h" // For the use of filters


uint8_t Voltage_Filter_Length(uint32_t length);
uint8_t Current_Filter_Length(uint32_t length);

float ADC_to_Value(uint32_t rawValue);
float Voltage_Conversion(float rawValue);
float Current_Conversion(float rawValue);

float Voltage_Offset();
float Voltage_DCLink();

float meas_Uab(float oldMeas);
float meas_Ubc(float oldMeas);
float meas_Uca(float oldMeas);

float meas_Ia(float oldMeas);
float meas_Ib(float oldMeas);
float meas_Ic(float oldMeas);

#endif /* INC_ADC_MEAS_H_ */
