/*
 * PLL.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Bausa
 */
/* Includes ------------------------------------------------------------------*/
#include "PLL.h"

/* Puplic variables ---------------------------------------------------------*/
static float temp1, temp2;

static float PIintegral, oldError, Kp, Ti, Ts, nom_freq;


uint8_t setPIdqPLL(float nom_f, float sampleFreq){
	nom_freq = nom_f;
	temp1 = 4.6f / ((1.0f/sqrtf(2.0f)) * nom_f);
	Kp = 9.2f / temp1;
	Ti = ((1.0f/sqrtf(2.0f)) * (1.0f/sqrtf(2.0f)) * temp1 * temp1)/21.16f;
	Ts = 1.0f/sampleFreq;
	return HAL_OK;

}

uint8_t dqPLL(float Ua, float Ub, float Uc, float* Theta, float* Ud){

	simpClarkeParkTrans(Ua, Ub, Uc, *Theta, Ud, &temp1);

	PIintegral +=  (Ts/2.0f) * (temp1 + oldError);
	oldError = temp1;
	temp1 = Kp*(temp1) + (PIintegral/Ti);

	temp1 += nom_freq;

	*Theta +=  (Ts/2.0f) * (temp1 + temp2);
	if (*Theta > 6.2831853072f) {
		*Theta -= 6.2831853072f;
	}

	temp2 = temp1;

	return HAL_OK;


}




