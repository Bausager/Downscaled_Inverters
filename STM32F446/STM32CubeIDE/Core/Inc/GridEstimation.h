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
#include "math.h" // Need for powf()
#include <stdlib.h> // Need for RAND_MAX

/*
 * GridEstiMeas
 * struct for grid measurements
 * float Vn: Line-Neutral voltage RMS. Could do and average over Ua, Ub and Uc.
 * float Pn: Plant Active Power
 * float Qn: Plant Reactive Power
 */
struct GridEstiMeas{
	float Vn;
	float Pn;
	float Qn;
};


/*
 * GridEstiVari
 * struct for grid estimations
 * float Eg: Grid RMS Voltage
 * float R: Grid Resistance
 * float X: Grid Reactance
 * float Error: Cost function error
 */
struct GridEstiVari{
	float Eg;
	float R;
	float X;
	float Error;
};


uint8_t InitiliseGridStruct(uint16_t N, struct GridEstiVari* values);
uint8_t argsort(uint16_t N, struct GridEstiVari* values);
uint8_t costFunctionJ(uint16_t M, struct GridEstiMeas* measVal, struct GridEstiVari* EstiVal);
uint8_t GeneticandRandomSearch(uint16_t N, uint16_t M, struct GridEstiMeas* measVal, struct GridEstiVari* EstiVal);





#endif /* INC_GRIDESTIMATION_H_ */
