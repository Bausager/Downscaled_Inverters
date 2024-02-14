/*
 * measCalc.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

/* Includes ------------------------------------------------------------------*/
#include "measCalc.h"

/* Puplic variables ---------------------------------------------------------*/
static const float sqrt3 = 1.0f/sqrt(3);


uint8_t instantaneousPower(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q){
	float Ua = (Uab + Uac)/3.0f;
	float Ub = (Ubc - Uab)/3.0f;
	float Uc = (-Uac - Ubc)/3.0f;

	*P = (Ua*Ia) + (Ub*Ib) + (Uc*Ic);
	*Q = sqrt3*((Ia*-Ubc) + (Ib*Uac) + (Ic*-Uab));

	return HAL_OK;
}
