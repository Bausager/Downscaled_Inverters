/*
 * adc_handler.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */
/* Includes ------------------------------------------------------------------*/
#include "adc_handler.h"

const uint32_t ADC_channels[16] = {ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7, ADC_CHANNEL_8, ADC_CHANNEL_9,
									ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14, ADC_CHANNEL_15};

uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal){
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	sConfig.Channel = ADC_channels[Channal];

	if(ADC_number == 1){
		if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(ADC_number == 2){
		if(HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(ADC_number == 3){
		if(HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else{
		Error_Handler();
	}
	return HAL_OK;
}

uint32_t adc_voltage_ph12(){

	ADC_Selector(1,10);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc1) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc1);

}
uint32_t adc_voltage_ph13(){

	ADC_Selector(2,12);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc2) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc2);
}
uint32_t adc_voltage_ph23(){

	ADC_Selector(3,0);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc3) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc3);
}

uint32_t adc_current_ph1(){

	ADC_Selector(1,11);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc1) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc1);
}
uint32_t adc_current_ph2(){

	ADC_Selector(2,13);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc2) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return  HAL_ADC_GetValue(&hadc2);
}
uint32_t adc_current_ph3(){

	ADC_Selector(3,1);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc3) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc3);
}


uint32_t adc_voltage_offset(){

	ADC_Selector(1,4);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc1) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc1);
}
uint32_t adc_voltage_DClink(){

	ADC_Selector(2,6);

	// Start ADC Conversion
	if(HAL_ADC_Start(&hadc2) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}

	// Wait for conversion to complete
	if(HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY) != HAL_OK) {
		// Error Handler
		Error_Handler();
	}
	// Read the ADC Value
	return HAL_ADC_GetValue(&hadc2);
}


