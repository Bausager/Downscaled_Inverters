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

#include <string.h> // sprintf
#include <stdio.h> // input/output

extern UART_HandleTypeDef huart2;

struct gridMeasValues{
	float Vn;
	float Pn;
	float Qn;
};

struct GridEstimationValues{
	float Eg;
	float R;
	float X;
	float Error;
};
void writeValueToUART1(double value);
uint8_t InitiliseGridStruct(uint16_t N, struct GridEstimationValues* values);
uint8_t argsort(uint16_t N, struct GridEstimationValues* values);
uint8_t costFunctionJ(uint16_t M, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal);
uint8_t GeneticandRandomSearch(uint16_t N, uint16_t M, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal);





#endif /* INC_GRIDESTIMATION_H_ */
