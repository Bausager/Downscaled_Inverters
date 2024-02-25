/*
 * measCalc.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Bausa
 */

/* Includes ------------------------------------------------------------------*/
#include "measCalc.h"

/*
 * Filter coefficients for power and RMS filters
 */
static float powerFilterCoeff, rmsFilterCoeff;


/*
 * Function:  RMS_Filter_Length
 * -----------------------------
 *	computes an filter coefficient that's between: [0,1]
 *
 *  const uint32_t length: the sample length of the filter coefficient
 *
 *  returns: HAL status
 */
uint8_t RMS_Filter_Length(const uint32_t length){
	if(length <= 0){
		rmsFilterCoeff = 0;
	}else{
		rmsFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

/*
 * Function:  Power_Filter_Length
 * ------------------------------
 *	computes an filter coefficient that's between: [0,1]
 *
 *	const uint32_t length: the sample length of the filter coefficient
 *
 *	returns: HAL status
 */
uint8_t Power_Filter_Length(const uint32_t length){
	if(length <= 0){
		powerFilterCoeff = 0;
	}else{
		powerFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

/*
 * Function:  calc_RMS
 * --------------------
 *	computes an approximation of the RMS for three values using the same RMS filter coefficient:
 *
 *	const float Ua: First value.
 *	const float Ub: Second value.
 *	const float Uc: Third value.
 *
 *	float* UaRMS: First filtered variable pointer
 *	float* UbRMS: Second filtered variable pointer
 *	float* UcRMS: Third filtered variable pointer
 *
 *	returns: HAL status
 */
uint8_t calc_RMS(const float Ua, const float Ub, const float Uc, float* UaRMS, float* UbRMS, float* UcRMS){
	*UaRMS = RMS_Filter(rmsFilterCoeff, Ua, *UaRMS);
	*UbRMS = RMS_Filter(rmsFilterCoeff, Ub, *UbRMS);
	*UcRMS = RMS_Filter(rmsFilterCoeff, Uc, *UcRMS);
	return HAL_OK;
}


/*
 * Function:  calc_Instantaneous_Power
 * -----------------------------------
 *	computes the instantaneous active and reactive power and filters the the results using the power filter coefficient:
 *
 *	const float Ua: Line voltage for Phase A
 *	const float Ub: Line voltage for Phase B
 *	const float Uc: Line voltage for Phase C
 *	const float Ia: Line current for Phase A
 *	const float Ib: Line current for Phase B
 *	const float Ic: Line current for Phase C
 *
 *	float* P: Filtered active power variable pointer
 *	float* Q: Filtered reactive power variable pointer
 *
 *	returns: HAL status
 *
 *	Literature:
 *	@Patten Name:  Variable speed wind turbine having a passive grid side rectifier with scalar power control and dependent pitch control
 *	@Patten Number: US7015595B2
 */
uint8_t calc_Instantaneous_Power(const float Ua, const float Ub, const float Uc, const float Ia, const float Ib, const float Ic, float* P, float* Q){
	*P = exponential_Filter(powerFilterCoeff, (Ua*Ia) + (Ub*Ib) + (Uc*Ic), *P);
	*Q = exponential_Filter(powerFilterCoeff, (0.57735f*((Ia*(Uc - Ub)) + (Ib*(Ua - Uc)) + (Ic*(Ub - Ua)))), *Q);

	return HAL_OK;
}

/*
 * Function:  calc_Power_Factor
 * -----------------------------
 *	computes the power factor for the system
 *
 *	const float P: Active power
 *	const float Q: Reactive power
 *
 *	returns: Power factor
 */
float calc_Power_Factor(const float P, const float Q){
	return (P / (sqrtf(P*P) + sqrtf(Q*Q)));
}

/*
 * Function:  calc_Uxx_to_Uxn
 * ---------------------------
 *	computes the instantaneous line-neutral voltages from line-line voltages
 *
 *	const float Uab: Line-line voltage for Phase A-B
 *	const float Ubc: Line-line voltage for Phase B-C
 *	const float Uca: Line-line voltage for Phase C-A
 *
 *	float Ua: Line-neutral voltage for Phase A variable pointer
 *	float Ub: Line-neutral voltage for Phase B variable pointer
 *	float Uc: Line-neutral voltage for Phase C variable pointer
 *
 *	returns: HAL status
 */
uint8_t calc_Uxx_to_Uxn(const float Uab, const float Ubc, const float Uca, float* Ua, float* Ub, float* Uc){
	*Ua = (Uab - Uca)/3.0f;
	*Ub = (Ubc - Uab)/3.0f;
	//*Uc = (Uca - Ubc)/3.0f;
	*Uc = -*Ua - *Ub;

	return HAL_OK;
}
