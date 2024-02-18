/*
 * GridEstimation.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Bausa
 */

#include "GridEstimation.h"

static const float low = 0.99;
static const float high = 1.01;
static uint16_t c;
static uint8_t argsortFlag = 1;


uint8_t InitiliseGridStruct(uint16_t N, struct GridEstimationValues* values){
	c = ceil(0.25f*(float)N);
	for (int i = 0; i < N; ++i) {
		values[i].Eg = (low*(float)rand())*(high - low)/RAND_MAX;
		values[i].R = (low*(float)rand())*(high - low)/RAND_MAX;
		values[i].X = (low*(float)rand())*(high - low)/RAND_MAX;
	}

	return HAL_OK;
}

uint8_t argsort(uint16_t N, struct GridEstimationValues* values){

	for (uint16_t ii = 0; ii < N; ++ii) {
		for (uint16_t i = 0; i < N - 1; i++){
			if(values[i].Error > values[i + 1].Error){
				//https://stackoverflow.com/questions/36746296/how-to-swap-struct-elements-of-array-inside-a-struct-c
				struct GridEstimationValues temp = values[i];

				values[i] = values[i + 1];
				values[i + 1] = temp;
			}
		}
	}
	return HAL_OK;
}



uint8_t costFunctionJ(uint16_t N, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal){

	for (int i = 0; i < N; i++) {
		EstiVal[i].Error = 0;
		for (int ii = 0; ii < N; ii++) {
			float temp1 = (pow(measVal[ii].Vn,2.0f) - pow(EstiVal[i].Eg,2.0f));
			float temp2 = (((pow(EstiVal[i].R,2.0f) + pow(EstiVal[i].X,2.0f)) * (pow(measVal[ii].Pn,2.0f) + pow(measVal[ii].Qn,2.0f))) / (9.0f*pow(measVal[ii].Vn,2.0f)));
			float temp3 = (2.0f*(((EstiVal[i].R*measVal[ii].Pn) + (EstiVal[i].X*measVal[ii].Qn))/3.0f));
			EstiVal[i].Error += pow(temp2,2.0f);


			/*if(isnan(EstiVal[i].Error) || isinf(EstiVal[i].Error)){
				EstiVal[i].Error = 10e3;
			}*/
		}

	}
	return HAL_OK;
}

uint8_t GeneticandRandomSearch(uint16_t N, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal){

	for (int i = 1; i < N; i++) {
		if (i < c) {
			EstiVal[i].Eg *= (low*(float)rand())*(high - low)/RAND_MAX;
			EstiVal[i].R *= (low*(float)rand())*(high - low)/RAND_MAX;
			EstiVal[i].X *= (low*(float)rand())*(high - low)/RAND_MAX;
		}else{
			EstiVal[i].Eg = (float)rand()*10.0f/RAND_MAX;
			EstiVal[i].R = (float)rand()*100.0f/RAND_MAX;
			EstiVal[i].X = (float)rand()*1.0f/RAND_MAX;
		}
	}

	costFunctionJ(N, measVal, EstiVal);
	argsort(N, EstiVal);

	return HAL_OK;
}
