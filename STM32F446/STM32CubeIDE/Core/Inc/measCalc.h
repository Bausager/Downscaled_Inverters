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
#include "filter.h" // For filter functions


uint8_t RMS_Filter_Length(const uint32_t length);
uint8_t Power_Filter_Length(const uint32_t length);
uint8_t calc_Instantaneous_Power(const float Ua, const float Ub, const float Uc, const float Ia, const float Ib, const float Ic, float* P, float* Q);
float calc_Power_Factor(const float P, const float Q);
uint8_t calc_RMS(const float Ua, const float Ub, const float Uc, float* UaRMS, float* UbRMS, float* UcRMS);
uint8_t calc_Uxx_to_Uxn(const float Uab, const float Uac, const float Ubc, float* Ua, float* Ub, float* Uc);





#endif /* INC_MEASCALC_H_ */
