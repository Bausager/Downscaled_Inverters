/*
 * filter.h
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h" // For sqrf() function

float exponential_Filter(float alpha, float oldMeas, float newMeas);
float RMS_Filter(float rmsFilterCoeff, float newMeas, float rmsValue);


#endif /* INC_FILTER_H_ */
