/*
 * adc_meas.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */
/* Includes ------------------------------------------------------------------*/
#include "adc_meas.h"

/* Puplic variables ---------------------------------------------------------*/
static float temp, voltageFilterCoeff, currentFilterCoeff;

static float Uab, Uac, Ubc, Ia, Ib, Ic;

static float offset = 1.65f;
static float DCLink = 5.0f;

static const float initializingFilterCoeff = 0.999f;
static const float ADCConverstionRate = 3.3f/4095.0f;
static const float VoltageConverstionRate = 1.0f / (510.0f/3300.0f);
static const float CurrentConverstionRate = 1.0f/ ((1.5f*20.0f)/2.0f);



uint8_t setVoltageFilterCoeff(float coeff){
	voltageFilterCoeff = coeff;
	return HAL_OK;
}
uint8_t setCurrentFilterCoeff(float coeff){
	currentFilterCoeff = coeff;
	return HAL_OK;
}


float ADCtoValue(uint32_t rawValue){
	return ((float)rawValue * ADCConverstionRate);
}
float PhaseVoltageConversion(float rawValue){
	return (rawValue * VoltageConverstionRate);
}
float PhaseCurrentConversion(float rawValue){
	return (rawValue * CurrentConverstionRate);
}

float Voltage_Offset(){
	temp = ADCtoValue(adc_voltage_offset());
	offset = exponentialFilter(initializingFilterCoeff, offset, temp);
	return offset;


}
float Voltage_DCLink(){
	temp = (ADCtoValue(adc_voltage_DClink())) * 2.0f;
	DCLink = exponentialFilter(initializingFilterCoeff, DCLink, temp);
	return DCLink;
}

float Voltage_Ph12(float oldMeas){
	temp = PhaseVoltageConversion(ADCtoValue(adc_voltage_ph12()) - offset);
	return exponentialFilter(voltageFilterCoeff, oldMeas, temp);
}
float Voltage_Ph13(float oldMeas){
	temp = PhaseVoltageConversion(ADCtoValue(adc_voltage_ph13()) - offset);
	return exponentialFilter(voltageFilterCoeff, oldMeas, temp);
}
float Voltage_Ph23(float oldMeas){
	temp = PhaseVoltageConversion(ADCtoValue(adc_voltage_ph23()) - offset);
	return exponentialFilter(voltageFilterCoeff, oldMeas, temp);
}

float Current_Ph1(float oldMeas){
	temp = PhaseCurrentConversion(ADCtoValue(adc_current_ph1()) - offset);
	return exponentialFilter(currentFilterCoeff, oldMeas, temp);
}
float Current_Ph2(float oldMeas){
	temp = PhaseCurrentConversion(ADCtoValue(adc_current_ph2()) - offset);
	return exponentialFilter(currentFilterCoeff, oldMeas, temp);
}
float Current_Ph3(float oldMeas){
	temp = PhaseCurrentConversion(ADCtoValue(adc_current_ph3()) - offset);
	return exponentialFilter(currentFilterCoeff, oldMeas, temp);
}







