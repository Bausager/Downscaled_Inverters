/*
 * ADCMeas.c
 *
 *  Created on: Feb 12, 2024
 *      Author: Bausa
 *      chatGPT siger:
 *
 *
 *
 */
#include "ADCMeas.h"


uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal){
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	if(ADC_number == 1){
		if(Channal == 0){
			sConfig.Channel = ADC_CHANNEL_0;
		}
		else if(Channal == 1){
			sConfig.Channel = ADC_CHANNEL_1;
		}
		else if(Channal == 2){
			sConfig.Channel = ADC_CHANNEL_2;
		}
		else if(Channal == 3){
			sConfig.Channel = ADC_CHANNEL_3;
		}
		else if(Channal == 4){
			sConfig.Channel = ADC_CHANNEL_4;
		}
		else if(Channal == 5){
			sConfig.Channel = ADC_CHANNEL_5;
		}
		else if(Channal == 6){
			sConfig.Channel = ADC_CHANNEL_6;
		}
		else if(Channal == 7){
			sConfig.Channel = ADC_CHANNEL_7;
		}
		else if(Channal == 8){
			sConfig.Channel = ADC_CHANNEL_8;
		}
		else if(Channal == 9){
			sConfig.Channel = ADC_CHANNEL_9;
		}
		else if(Channal == 10){
			sConfig.Channel = ADC_CHANNEL_10;
		}
		else if(Channal == 11){
			sConfig.Channel = ADC_CHANNEL_11;
		}
		else if(Channal == 12){
			sConfig.Channel = ADC_CHANNEL_12;
		}
		else if(Channal == 13){
			sConfig.Channel = ADC_CHANNEL_13;
		}
		else if(Channal == 14){
			sConfig.Channel = ADC_CHANNEL_14;
		}
		else if(Channal == 15){
			sConfig.Channel = ADC_CHANNEL_15;
		}
		if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(ADC_number == 2){
		if(Channal == 0){
			sConfig.Channel = ADC_CHANNEL_0;
		}
		else if(Channal == 1){
			sConfig.Channel = ADC_CHANNEL_1;
		}
		else if(Channal == 2){
			sConfig.Channel = ADC_CHANNEL_2;
		}
		else if(Channal == 3){
			sConfig.Channel = ADC_CHANNEL_3;
		}
		else if(Channal == 4){
			sConfig.Channel = ADC_CHANNEL_4;
		}
		else if(Channal == 5){
			sConfig.Channel = ADC_CHANNEL_5;
		}
		else if(Channal == 6){
			sConfig.Channel = ADC_CHANNEL_6;
		}
		else if(Channal == 7){
			sConfig.Channel = ADC_CHANNEL_7;
		}
		else if(Channal == 8){
			sConfig.Channel = ADC_CHANNEL_8;
		}
		else if(Channal == 9){
			sConfig.Channel = ADC_CHANNEL_9;
		}
		else if(Channal == 10){
			sConfig.Channel = ADC_CHANNEL_10;
		}
		else if(Channal == 11){
			sConfig.Channel = ADC_CHANNEL_11;
		}
		else if(Channal == 12){
			sConfig.Channel = ADC_CHANNEL_12;
		}
		else if(Channal == 13){
			sConfig.Channel = ADC_CHANNEL_13;
		}
		else if(Channal == 14){
			sConfig.Channel = ADC_CHANNEL_14;
		}
		else if(Channal == 15){
			sConfig.Channel = ADC_CHANNEL_15;
		}
		if(HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(ADC_number == 3){
		if(Channal == 0){
			sConfig.Channel = ADC_CHANNEL_0;
		}
		else if(Channal == 1){
			sConfig.Channel = ADC_CHANNEL_1;
		}
		else if(Channal == 2){
			sConfig.Channel = ADC_CHANNEL_2;
		}
		else if(Channal == 3){
			sConfig.Channel = ADC_CHANNEL_3;
		}
		else if(Channal == 4){
			sConfig.Channel = ADC_CHANNEL_4;
		}
		else if(Channal == 5){
			sConfig.Channel = ADC_CHANNEL_5;
		}
		else if(Channal == 6){
			sConfig.Channel = ADC_CHANNEL_6;
		}
		else if(Channal == 7){
			sConfig.Channel = ADC_CHANNEL_7;
		}
		else if(Channal == 8){
			sConfig.Channel = ADC_CHANNEL_8;
		}
		else if(Channal == 9){
			sConfig.Channel = ADC_CHANNEL_9;
		}
		else if(Channal == 10){
			sConfig.Channel = ADC_CHANNEL_10;
		}
		else if(Channal == 11){
			sConfig.Channel = ADC_CHANNEL_11;
		}
		else if(Channal == 12){
			sConfig.Channel = ADC_CHANNEL_12;
		}
		else if(Channal == 13){
			sConfig.Channel = ADC_CHANNEL_13;
		}
		else if(Channal == 14){
			sConfig.Channel = ADC_CHANNEL_14;
		}
		else if(Channal == 15){
			sConfig.Channel = ADC_CHANNEL_15;
		}
		if(HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	return HAL_OK;
}

