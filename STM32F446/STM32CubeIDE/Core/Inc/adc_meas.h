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
#include "filter.h"

/* Puplic variables ---------------------------------------------------------*/



uint8_t setVoltageFilterCoeff(float coeff);
uint8_t setCurrentFilterCoeff(float coeff);

float ADCtoValue(uint32_t rawValue);
float PhaseVoltageConversion(float rawValue);
float PhaseCurrentConversion(float rawValue);

float Voltage_Offset();
float Voltage_DCLink();

float Voltage_Ph12(float oldMeas);
float Voltage_Ph13(float oldMeas);
float Voltage_Ph23(float oldMeas);


float Current_Ph1(float oldMeas);
float Current_Ph2(float oldMeas);
float Current_Ph3(float oldMeas);

#endif /* INC_ADC_MEAS_H_ */
