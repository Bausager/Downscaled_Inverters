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
 * Exponential Filter
 * Input:
 * float alpha: Filter coefficient ([0,1])
 * float oldMeas: The filter variable
 * float newMeas: The new measurement
 * Output:
 * float exponential_Filter(...): The filtered value
 *
 * more information: https://en.wikipedia.org/wiki/Exponential_smoothing
 */
float exponential_Filter(float alpha, float oldMeas, float newMeas){
	// If filter coefficient is <=0, disable filter
	if (alpha <= 0) {
		return newMeas;
	}
	else{
		return ((alpha*oldMeas) + ((1.0f-alpha)*newMeas));
	}

}

/*
 * RMS Filter
 * Input:
 * float rmsFilterLength: Normalised Filter Length [0,1], typical > 0.99 (multiply periods for nominal grid frequency).
 * float rmsValue: The filter variable
 * float newMeas: The new measurement
 * Output:
 * float RMS_Filter(...): The RMS value
 */
float RMS_Filter(float rmsFilterLength, float rmsValue, float newMeas){
	// Calculate the Root-Squre
	temp = sqrtf(newMeas * newMeas);
	// Use exponential_Filter with a long filter length for RMS accumulation (multiply periods).
	return exponential_Filter(1 - rmsFilterLength, rmsValue, temp);

}
