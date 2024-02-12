/*
 * ADCMeas.h
 *
 *  Created on: Feb 12, 2024
 *      Author: Bausa
 */

#ifndef INC_ADCMEAS_H_
#define INC_ADCMEAS_H_

#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;


uint8_t ADC_Selector(uint8_t ADC_number, uint8_t Channal);



#endif /* INC_ADCMEAS_H_ */
