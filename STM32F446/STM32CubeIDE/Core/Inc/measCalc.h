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
#include "math.h"

uint8_t setPowerFilterCoeff(float coeff);

uint8_t instantaneousPower(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q);

float powerFactor(float P, float Q);





#endif /* INC_MEASCALC_H_ */
