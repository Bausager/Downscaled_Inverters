/*
 * GridEstimation.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Bausa
 */

#include "GridEstimation.h"

static const float low = 0.990;
static const float high = 1.001;
static uint16_t c;

void writeValueToUART1(double value){
	char outputBuffer[256];
	uint8_t len = snprintf(outputBuffer, sizeof(outputBuffer), "Value: %lf \r\n", value);
	HAL_UART_Transmit(&huart2, (uint8_t *)outputBuffer, len, 100);
}


uint8_t InitiliseGridStruct(uint16_t N, struct GridEstimationValues* values){
	c = ceil(0.25f*(float)N);
	for (int i = 0; i < N; ++i) {
		values[i].Eg = (float)rand()*10.0f/RAND_MAX;
		values[i].R = (float)rand()*100.0f/RAND_MAX;
		values[i].X = (float)rand()*1.0f/RAND_MAX;
		values[i].Error = (float)rand();
	}
	argsort(N, values);
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
	EstiVal->Error = 0;
	for (uint16_t i = 0; i < N; ++i) {
			float temp1 = (pow(measVal[i].Vn,2.0f) - pow(EstiVal->Eg,2.0f));
			float temp2 = (pow(EstiVal->R,2.0f) + pow(EstiVal->X,2.0f));
			float temp3 = (pow(measVal[i].Pn,2.0f) + pow(measVal[i].Qn,2.0f));
			float temp4 = (9.0f*pow(measVal[i].Vn,2.0f));
			float temp5 = (2.0f*(((EstiVal->R*measVal[i].Pn) + (EstiVal->X*measVal[i].Qn))/3.0f));
			EstiVal->Error += pow(temp1 + (temp2*temp3)/temp4 - temp5,2.0f);
	}
	return HAL_OK;
}

uint8_t GeneticandRandomSearch(uint16_t N, uint16_t M, struct gridMeasValues* measVal, struct GridEstimationValues* EstiVal){

	for (uint16_t i = 1; i < M; ++i) {
		if (i < c) {
			EstiVal[i].Eg *= (low + (((float)rand()/RAND_MAX)*(high - low)));
			EstiVal[i].R *= (low + (((float)rand()/RAND_MAX)*(high - low)));
			EstiVal[i].X *= (low + (((float)rand()/RAND_MAX)*(high - low)));

		}else{
			EstiVal[i].Eg = (((float)rand()/RAND_MAX)*5.f);
			EstiVal[i].R = (((float)rand()/RAND_MAX)*1000.f);
			EstiVal[i].X = (((float)rand()/RAND_MAX)*10.f);
		}
	}

	//writeValueToUART1(EstiVal[M-5].Eg);
	for (uint16_t i = 0; i < M; ++i) {
		costFunctionJ(N, measVal, &EstiVal[i]);
	}

	argsort(M, EstiVal);

	return HAL_OK;
}
