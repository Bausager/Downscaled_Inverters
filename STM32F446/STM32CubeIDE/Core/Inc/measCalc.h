/*
 * measCalc.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

#ifndef INC_MEASCALC_H_
#define INC_MEASCALC_H_

/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include "filter.h"
#include "math.h"


uint8_t RMS_Filter_Length(uint32_t length);
uint8_t Power_Filter_Length(uint32_t length);

uint8_t calc_Instantaneous_Power(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q);
float calc_Power_Factor(float P, float Q);

uint8_t calc_RMS(float Ua, float Ub, float Uc, float* UaRMS, float* UbRMS, float* UcRMS);
uint8_t calc_Uxx_to_Uxn(float Uab, float Uac, float Ubc, float* Ua, float* Ub, float* Uc);





#endif /* INC_MEASCALC_H_ */
