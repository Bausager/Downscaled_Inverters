/*
 * measCalc.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

/* Includes ------------------------------------------------------------------*/
#include "measCalc.h"

/* Puplic variables ---------------------------------------------------------*/
static float powerFilterCoeff, rmsFilterCoeff;

uint8_t RMS_Filter_Length(uint32_t length){
	if(length <= 0){
		rmsFilterCoeff = 0;
	}else{
		rmsFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

uint8_t Power_Filter_Length(uint32_t length){
	if(length <= 0){
		powerFilterCoeff = 0;
	}else{
		powerFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}


uint8_t calc_RMS(float Ua, float Ub, float Uc, float* UaRMS, float* UbRMS, float* UcRMS){
	*UaRMS = RMS_Filter(rmsFilterCoeff, *UaRMS, Ua);
	*UbRMS = RMS_Filter(rmsFilterCoeff, *UbRMS, Ub);
	*UcRMS = RMS_Filter(rmsFilterCoeff, *UcRMS, Uc);
	return HAL_OK;
}



uint8_t calc_Instantaneous_Power(float Ua, float Ub, float Uc, float Ia, float Ib, float Ic, float* P, float* Q){
	*P = exponential_Filter(powerFilterCoeff, (Ua*Ia) + (Ub*Ib) + (Uc*Ic), *P);
	*Q = exponential_Filter(powerFilterCoeff, (0.57735f*((Ia*(Uc - Ub)) + (Ib*(Ua - Uc)) + (Ic*(Ub - Ua)))), *Q);

	return HAL_OK;
}

float powerFactor(float P, float Q){
	return (P / (sqrtf(P*P) + sqrtf(Q*Q)));
}

uint8_t calc_Uxx_to_Uxn(float Uab, float Ubc, float Uca, float* Ua, float* Ub, float* Uc){
	*Ua = (Uab - Uca)/3.0f;
	*Ub = (Ubc - Uab)/3.0f;
	//*Uc = (Uca - Ubc)/3.0f;
	*Uc = -*Ua - *Ub;
	return HAL_OK;
}
