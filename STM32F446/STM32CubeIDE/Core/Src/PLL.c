/*
 * PLL.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Bausa
 */
/* Includes ------------------------------------------------------------------*/
#include "PLL.h"

/*
 * Helper variables for calculations
 */
static float temp1;

/*
 * General PLL Variables
 */
static float natural_frequency, TsCoeff;

/*
 * dqPLL variables
 */
static float dqPLLKp, dqPLLTi, dqPLLnewError, dqPLLoldError, dqPLLoldTheta;


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
	natural_frequency = nom_f;
	TsCoeff = (1.0f/sampleFreq) / 2.0f;

	float settling_time = 4.6f/(0.70710f * nom_f);
	dqPLLKp = 9.2f / settling_time;
	dqPLLTi = ((0.49999 * settling_time * settling_time)/21.16f)/TsCoeff;
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
 *  returns: HAL status
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
uint8_t dqPLL(const float Ua, const float Ub, const float Uc, float* Theta, float* Ud){

	transf_abc_to_dq(Ua, Ub, Uc, *Theta, Ud, &dqPLLnewError);

	temp1 = dqPLLKp*(dqPLLnewError + (dqPLLTi*(dqPLLnewError + dqPLLoldError)));
	dqPLLoldError = dqPLLnewError;

	temp1 += natural_frequency;

	*Theta +=  TsCoeff * (temp1 + dqPLLoldTheta);
	if (*Theta > 6.2831853072f) {
		*Theta -= 6.2831853072f;
	}

	dqPLLoldTheta = temp1;

	return HAL_OK;


}




