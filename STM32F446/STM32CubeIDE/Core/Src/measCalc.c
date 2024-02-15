/*
 * measCalc.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

/* Includes ------------------------------------------------------------------*/
#include "measCalc.h"
#include "filter.h"

/* Puplic variables ---------------------------------------------------------*/
static const float oneOverSqrt3 = 1.0f/sqrt(3.0f);
static float powerFilterCoeff;

uint8_t setPowerFilterCoeff(float coeff){
	powerFilterCoeff = coeff;
	return HAL_OK;
}


uint8_t instantaneousPower(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q){
	float Ua = (Uab + Uac)/3.0f;
	float Ub = (Ubc - Uab)/3.0f;
	float Uc = (-Uac - Ubc)/3.0f;



	*P = exponentialFilter(powerFilterCoeff, *P, (Ua*Ia) + (Ub*Ib) + (Uc*Ic));
	*Q = exponentialFilter(powerFilterCoeff, *Q, oneOverSqrt3*((Ia*-Ubc) + (Ib*Uac) - (Ic*+Uab)));

	return HAL_OK;
}


float powerFactor(float P, float Q){
	return (P / (sqrt(P*P) + sqrt(Q*Q)));
}
