/*
 * adc_handler.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */
/* Includes ------------------------------------------------------------------*/
#include "adc_handler.h"


/*
 * ADC Channel Array
 */
const uint32_t ADC_channels[16] = {ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7, ADC_CHANNEL_8, ADC_CHANNEL_9,
									ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14, ADC_CHANNEL_15};

/*
 * ADC Selector
 * ADC_number: The ADC you want to use. Eg. 1; 2; 3.
 * Channel: Which ADC channel you want to use. Eg. 0; 7; 13.
 */
uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal){
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	sConfig.Channel = ADC_channels[Channal];
	
	/*
	 * Configures the selected ADC to the chosen channel
	 */
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

/*
 * Direct measures the voltages on the PCB.
 */
uint32_t ADC_Uab(){

	// Selects the correct ADC
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
uint32_t ADC_Uac(){

	// Selects the correct ADC
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
uint32_t ADC_Ubc(){

	// Selects the correct ADC
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

/*
 * Direct measures the currents on the PCB.
 */
uint32_t ADC_Ia(){

	// Selects the correct ADC
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
uint32_t ADC_Ib(){

	// Selects the correct ADC
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
uint32_t ADC_Ic(){

	// Selects the correct ADC
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

/*
 * Direct measures the voltage offset for configure the measurements
 */
uint32_t ADC_Offset(){

	// Selects the correct ADC
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

/*
 * Direct measures the voltage on the DC Link
 */
uint32_t ADC_DClink(){

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


