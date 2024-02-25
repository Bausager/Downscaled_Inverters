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

float exponential_Filter(const float alpha, const float oldMeas, const float newMeas);
float RMS_Filter(const float rmsFilterCoeff, const float newMeas, const float rmsValue);


#endif /* INC_FILTER_H_ */
