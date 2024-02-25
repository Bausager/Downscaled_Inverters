/*
 * filter.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

/* Includes ------------------------------------------------------------------*/
#include "filter.h"


/*
 * Helper variable for calculations
 */
static float temp;

/*
 * Function:  exponential_Filter
 * ------------------------------
 *	Uses an exponential filter as a low-pass filter
 *
 *	const float alpha: Filter coefficient
 *	const float newMeas: The new measurements
 *	const float oldMeas: The filtered variable used for the filtered value
 *
 *	returns: Filtered value
 *
 *	Wiki: https://en.wikipedia.org/wiki/Exponential_smoothing
 *
 */
float exponential_Filter(const float alpha, const float newMeas, const float oldMeas){
	// If filter coefficient is <=0, disable filter
	if (alpha <= 0) {
		return newMeas;
	}
	else{
		return ((alpha*oldMeas) + ((1.0f-alpha)*newMeas));
	}

}

/*
 * Function:  RMS_Filter
 * ----------------------
 *	Calculates the RMS value over a specific length using an exponential filter
 *
 *	const float rmsFilterCoeff: RMS filter coefficient
 *	const float newMeas: The new measurements
 *	const float rmsValue: Filtered RMS variable
 *
 *	returns: Filtered RMS value
 */
float RMS_Filter(const float rmsFilterCoeff, const float newMeas, const float rmsValue){
	// Calculate the Root-Squre
	temp = sqrtf(newMeas * newMeas);
	// Use exponential_Filter with a long filter length for RMS accumulation (multiply periods).
	return exponential_Filter(rmsFilterCoeff, temp, rmsValue);

}
