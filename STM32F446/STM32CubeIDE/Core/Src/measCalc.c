/*
 * measCalc.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

/* Includes ------------------------------------------------------------------*/
#include "measCalc.h"

/* Puplic variables ---------------------------------------------------------*/
static const float oneOverSqrt3 = 1.0f/sqrtf(3.0f);
static float powerFilterCoeff, rmsFilterLength;
static float _Ua, _Ub, _Uc;

uint8_t calcRMS(float* UaRMS, float* UbRMS, float* UcRMS, float Uab, float Uac, float Ubc){
	*UaRMS = RMSFilter(rmsFilterLength, *UaRMS, _Ua);
	*UbRMS = RMSFilter(rmsFilterLength, *UbRMS, _Ub);
	*UcRMS = RMSFilter(rmsFilterLength, *UcRMS, _Uc);
	return HAL_OK;
}

uint8_t setRMSFilterLength(uint32_t coeff){
	rmsFilterLength = (1.0f/(float)coeff);
	return HAL_OK;
}

uint8_t setPowerFilterCoeff(float coeff){
	powerFilterCoeff = coeff;
	return HAL_OK;
}

uint8_t instantaneousPower(float Uab, float Uac, float Ubc, float Ia, float Ib, float Ic, float* P, float* Q){
	_Ua = (Uab + Uac)/3.0f;
	_Ub = (Ubc - Uab)/3.0f;
	_Uc = (-Uac - Ubc)/3.0f;

	*P = exponentialFilter(powerFilterCoeff, *P, (_Ua*Ia) + (_Ub*Ib) + (_Uc*Ic));
	*Q = exponentialFilter(powerFilterCoeff, *Q, oneOverSqrt3*((Ia*-Ubc) + (Ib*Uac) - (Ic*+Uab)));

	return HAL_OK;
}


float powerFactor(float P, float Q){
	return (P / (sqrtf(P*P) + sqrtf(Q*Q)));
}
