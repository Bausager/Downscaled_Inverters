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

uint8_t calcRMS(float* UaRMS, float* UbRMS, float* UcRMS, float Ua, float Ub, float Uc){
	*UaRMS = RMS_Filter(rmsFilterLength, *UaRMS, Ua);
	*UbRMS = RMS_Filter(rmsFilterLength, *UbRMS, Ub);
	*UcRMS = RMS_Filter(rmsFilterLength, *UcRMS, Uc);
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

uint8_t instantaneousPower(float Ua, float Ub, float Uc, float Ia, float Ib, float Ic, float* P, float* Q){
	*P = exponential_Filter(powerFilterCoeff, *P, (Ua*Ia) + (Ub*Ib) + (Uc*Ic));
	*Q = exponential_Filter(powerFilterCoeff, *Q, oneOverSqrt3*((Ia*(Uc-Ub)) + (Ib*(Ua-Uc)) - (Ic*(Ub-Ua))));

	return HAL_OK;
}

float powerFactor(float P, float Q){
	return (P / (sqrtf(P*P) + sqrtf(Q*Q)));
}

uint8_t phaseNeutralCalc(float Uab, float Uac, float Ubc, float* Ua, float* Ub, float* Uc){
	*Ua = (Uab + Uac)/3.0f;
	*Ub = (Ubc - Uab)/3.0f;
	*Uc = (-Uac - Ubc)/3.0f;

	return HAL_OK;
}
