/*
 * PLL.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Bausa
 */
/* Includes ------------------------------------------------------------------*/
#include "PLL.h"


/*
 * Calculation for LCL phase-shift
 */
const float Li = 0.001f * 3.0f;
const float Ri = 3.7f * 3.0f;

const float Cf = (1.0f / 1000000.0f) * 4.0f;
const float Rf = 0.0f / 4.0f;

const float Lg = 0.001f * 2.0f;
const float Rg = 3.7f * 2.0f;


/*
 * Helper variables for calculations
 */
static float temp1;

/*
 * General PLL Variables
 */
static float angle, natural_angular_frequency, TsCoeff, filterAngleCompensation;

/*
 * dqPLL variables
 */
static float dqPLLKp, dqPLLTi, dqPLLnewError, dqPLLoldError, dqPLLoldTheta;

/*
 * Function:  LCL_Angle_Compensation
 * ---------------------------------
 *	Computes the angle difference from before the LCL filter to the point of measuring/point of coupling
 *
 *  const float nom_f: Nominal/natural grid frequency
 *
 *  returns: HAL status
 *
 */
uint8_t LCL_Angle_Compensation(const float nom_f){
	natural_angular_frequency = nom_f * 2.0f*3.1415f;

	float a1 = 1.0f;
	float b1 = Cf*Rf*natural_angular_frequency;

	float a2 = Cf * (Lg*(Rf+Ri) + Li*(Rf+Rg))*(-1.0f)*natural_angular_frequency*natural_angular_frequency + Rg + Ri;
	float b2 = Lg*Li*Cf*(-1.0f)*natural_angular_frequency*natural_angular_frequency*natural_angular_frequency + (Lg + Li + Cf*(Rf*Rg + Rf*Ri + Rg*Ri))*natural_angular_frequency;

	float Re = (a1*a2 + b1*b2)/(a2*a2 + b2*b2);
	float Im = (a2*b1 - a1*b2)/(a2*a2 + b2*b2);

	filterAngleCompensation = atanf(Im/Re);

	return HAL_OK;
}

/*
 * Function:  dqPLL_Config
 * ------------------------
 *	Configures dqPLL internal coefficients and PI controller
 *
 *  const float nom_f: Nominal/natural grid frequency
 *  const float sampleFreq: Sample frequency
 *
 *  returns: HAL status
 *
 */
uint8_t dqPLL_Config(const float nom_f, const float sampleFreq){
	natural_angular_frequency = nom_f * 2.0f*3.1415f;
	TsCoeff = (1.0f/sampleFreq) / 2.0f;

	float settling_time = 4.6f/(0.70710f * nom_f);
	dqPLLKp = 9.2f / settling_time;
	dqPLLTi = ((0.49999f * settling_time * settling_time)/21.16f)/TsCoeff;

	return HAL_OK;
}

/*
 * Function:  dqPLL
 * ----------------
 *	dq-Phase-Lock-Loop(dqPLL) for grid angle estimation and magnitude.
 *
 *  const float Ua: Line-neutral voltage for Phase A
 *  const float Ub: Line-neutral voltage for Phase B
 *  const float Uc: Line-neutral voltage for Phase C
 *
 *  float* Theta: Pointer to grid angle variable which is integrated upon
 *  float* Ud: Pointer to grid magnitude variable
 *
 *  returns: angle to use in Space-Vector-Modulation, PWM generation or alike.
 *
 *	@article{ALI2018434,
	title = {Three-phase phase-locked loop synchronization algorithms for grid-connected renewable energy systems: A review},
	journal = {Renewable and Sustainable Energy Reviews},
	volume = {90},
	pages = {434-452},
	year = {2018},
	issn = {1364-0321},
	doi = {https://doi.org/10.1016/j.rser.2018.03.086},
	url = {https://www.sciencedirect.com/science/article/pii/S1364032118301813},
	author = {Zunaib Ali and Nicholas Christofides and Lenos Hadjidemetriou and Elias Kyriakides and Yongheng Yang and Frede Blaabjerg}}
 */
float dqPLL(const float Ua, const float Ub, const float Uc, float* Theta, float* Ud){

	// Transforms it from abc domain to dq, with former angle at the point of measuring.
	transf_abc_to_dq(Ua, Ub, Uc, *Theta, Ud, &dqPLLnewError);

	// PI Controller to minimise the "error" (Uq)
	temp1 = dqPLLKp*(dqPLLnewError) + (dqPLLTi*(dqPLLnewError + dqPLLoldError));
	dqPLLoldError = dqPLLnewError;

	// Add the grid angular frequency
	temp1 += natural_angular_frequency;

	// Integrate over the estimated grid angular frequency to get the angle
	*Theta +=  (TsCoeff * (temp1 + dqPLLoldTheta));

	if (*Theta > 6.2831853072f) {
		*Theta -= 6.2831853072f;
	}
	dqPLLoldTheta = temp1;

	// Compensate the angle in the point of measuring with the angle shift from the LCL to get the angle for the PWM generation
	angle = *Theta + filterAngleCompensation;
	if (angle > 6.2831853072f) {
		angle -= 6.2831853072f;
	}else if (angle < 0.0f) {
		angle += 6.2831853072f;
	}

	return angle;
}




