/*
 * filter.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

/* Includes ------------------------------------------------------------------*/
#include "filter.h"


/* Puplic variables ---------------------------------------------------------*/
static float temp;

// https://en.wikipedia.org/wiki/Exponential_smoothing
float exponentialFilter(float alpha, float avg, float value){
	if (alpha <= 0) {
		return value;
	}
	else{
		return ((alpha*avg) + ((1.0f-alpha)*value));
	}

}

float RMSFilter(float rmsFilterLength, float rmsValue, float newValue){
	temp = sqrt(newValue * newValue);
	return exponentialFilter(1 - rmsFilterLength, rmsValue, temp);
	//return sqrtf(newValue*newValue*rmsFilterLength);

}
