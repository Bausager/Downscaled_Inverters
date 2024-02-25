/*
 * GridEstimation.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Bausa
 */

#include "GridEstimation.h"

/*
 * Variables for small perturbations for finding best grid estimation
 */
static const float low = 0.999;
static const float high = 1.001;

/*
 * Variable used for calculating the 0.25 of the total amount of list of grid estimating variables
 */
static uint16_t quarterLength;

/*
 * Function:  InitiliseGridStruct
 * ------------------------------
 *	Calculates the quarter length of the grid estimation list and initialise the variables to random variables; Eg from 0V to 10V, R from 0ohm to 100ohm, X from 0ohm to 1omh, Error a random integer
 *
 *  const uint16_t N: The length of the grid estimation list
 *
 *  struct GridEstiVari* values: list of structs of grid estimation variables
 *
 *  returns: HAL status
 */
uint8_t InitiliseGridStruct(const uint16_t N, struct GridEstiVari* values){
	// Calculate 0.25 of the length of N
	quarterLength = ceil(0.25f*(float)N);
	// Random initialising variables in GridEstiVari.
	for (int i = 0; i < N; ++i) {
		values[i].Eg = (float)rand()*10.0f/RAND_MAX;
		values[i].R = (float)rand()*100.0f/RAND_MAX;
		values[i].X = (float)rand()*1.0f/RAND_MAX;
		values[i].Error = (float)rand();
	}
	// Sorts the array, the lowest error first.
	argsort(N, values);

	return HAL_OK;
}

/*
 * Function:  argsort
 * ------------------
 *	Sorts through the list of grid estimation variables with the lowest error at the top
 *
 *  const uint16_t N: The length of the grid estimation list
 *
 *  struct GridEstiVari* values: list of structs of grid estimation variables
 *
 *  returns: HAL status
 */
uint8_t argsort(const uint16_t N, struct GridEstiVari* values){

	// Sorts the array. Lowest error first
	for (uint16_t ii = 0; ii < N; ++ii) {
		for (uint16_t i = 0; i < N - 1; i++){
			if(values[i].Error > values[i + 1].Error){
				//https://stackoverflow.com/questions/36746296/how-to-swap-struct-elements-of-array-inside-a-struct-c
				struct GridEstiVari temp = values[i];

				values[i] = values[i + 1];
				values[i + 1] = temp;
			}
		}
	}
	return HAL_OK;
}

/*
 * Function:  costFunctionJ
 * -------------------------
 *	Calculates the error for grid estimation values with the grid measurements.
 *	Under the assumption the grid can be modelled as a pi-circuit, which is most cases is a medium-length lines, from 20km to 250km
 *	You need a minimum of three measurements for the cost function to work
 *
 *  const uint16_t N: The length of the grid estimation list
 *  const struct GridEstiMeas* measVal: List of the grid measurements
 *
 *  struct GridEstiVari* EstiVal: List of the grid estimation values
 *
 *  returns: HAL status
 *
 *	Literature:
 *	@Conference paper: Online Method for the Estimation of the Short Circuit Ratio with Small Grid Perturbation
 *	@Conference paper authors: D. Obradovic, A. Szabo (Siemens, Germany), P. Egedal, K. B. Danielsen, B. Andresen, M. Stoettrup (Siemens Wind Power, Denmark) (WIW13‐1059)
 */
uint8_t costFunctionJ(uint16_t N, const struct GridEstiMeas* measVal, struct GridEstiVari* EstiVal){
	// Sets the error to 0, so it's not accumulate over multiply function calls
	EstiVal->Error = 0;
	// Calculating the error for the specific GridEstiVari
	for (uint16_t i = 0; i < N; ++i) {
			float temp1 = (powf(measVal[i].Vn,2.0f) - powf(EstiVal->Eg,2.0f));
			float temp2 = (powf(EstiVal->R,2.0f) + powf(EstiVal->X,2.0f));
			float temp3 = (powf(measVal[i].Pn,2.0f) + powf(measVal[i].Qn,2.0f));
			float temp4 = (9.0f*powf(measVal[i].Vn,2.0f));
			float temp5 = (2.0f*(((EstiVal->R*measVal[i].Pn) + (EstiVal->X*measVal[i].Qn))/3.0f));
			// Accumulate error over all measurements
			EstiVal->Error += pow(temp1 + (temp2*temp3)/temp4 - temp5,2.0f);
	}
	return HAL_OK;
}

/*
 * Function:  GeneticandRandomSearch
 * ---------------------------------
 *	Minimises an cost function.
 *	Here the best solution is untouched!
 *	Genetic aspect -> The 25% next best undergoes small perturbation
 *	Random search aspect -> the 75% worst gets randomised
 *
 *  const uint16_t N: The length of the grid measurement list
 *  const uint16_t M: The length of the grid estimation list
 *	const struct GridEstiMeas* measVal: List if grid measurements values
 *
 *  struct GridEstiVari* EstiVal: List if grid estimation values
 *
 *  returns: HAL status
 */
uint8_t GeneticandRandomSearch(const uint16_t N, const uint16_t M, const struct GridEstiMeas* measVal, struct GridEstiVari* EstiVal){


	 // The lowest error (EstiVal[0]) is not touched.
	for (uint16_t i = 1; i < M; ++i) {
		if (i < quarterLength) {
			// The other 25% lowest error changes with small perturbations.
			EstiVal[i].Eg *= (low + (((float)rand()/RAND_MAX)*(high - low)));
			EstiVal[i].R *= (low + (((float)rand()/RAND_MAX)*(high - low)));
			EstiVal[i].X *= (low + (((float)rand()/RAND_MAX)*(high - low)));

		}else{
			// The 75% rest are rerolled.
			EstiVal[i].Eg = (((float)rand()/RAND_MAX)*5.0f);
			EstiVal[i].R = (((float)rand()/RAND_MAX)*1000.0f);
			EstiVal[i].X = (((float)rand()/RAND_MAX)*10.0f);
		}
	}

	// The error it recalculated for each grid estimation
	for (uint16_t i = 0; i < M; ++i) {
		costFunctionJ(N, measVal, &EstiVal[i]);
	}

	// The list of grid estimation is sorted by the error. Lowest error first.
	argsort(M, EstiVal);

	return HAL_OK;
}
