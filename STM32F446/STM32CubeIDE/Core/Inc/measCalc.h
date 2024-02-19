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

uint8_t setPowerFilterCoeff(float coeff);
uint8_t setRMSFilterLength(uint32_t coeff);

uint8_t instantaneousPower(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q);
uint8_t getUx(float* Ua, float* Ub, float* Uc);
float powerFactor(float P, float Q);

uint8_t calcRMS(float* UaRMS, float* UbRMS, float* UcRMS, float Uab, float Uac, float Ubc);
uint8_t phaseNeutralCalc(float Uab, float Uac, float Ubc, float* Ua, float* Ub, float* Uc);





#endif /* INC_MEASCALC_H_ */
