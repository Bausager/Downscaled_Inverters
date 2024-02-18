/*
 * GridEstimation.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Bausa
 */

#ifndef INC_GRIDESTIMATION_H_
#define INC_GRIDESTIMATION_H_
/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include "math.h"
#include <stdlib.h>


struct gridMeasValues{
	float Vn;
	float Pn;
	float Qn;
};

struct GridEstimationValues{
	float Eg;
	float R;
	float X;
	double Error;
};

uint8_t InitiliseGridStruct(uint16_t N, struct GridEstimationValues* values);
uint8_t argsort(uint16_t N, struct GridEstimationValues* values);
uint8_t costFunctionJ(uint16_t N, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal);
uint8_t GeneticandRandomSearch(uint16_t N, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal);





#endif /* INC_GRIDESTIMATION_H_ */
