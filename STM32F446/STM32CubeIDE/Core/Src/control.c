/*
 * control.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Bausa
 */

#include "control.h"


float _TsCoeff, _Kp, _Kq;


uint8_t Droop_Config(float Kp, float Kq, float sampleFreq){
	_Kp = Kp;
	_Kq = Kq;
	_TsCoeff = (1.0f/sampleFreq) / 2.0f;

	return HAL_OK;
}


uint8_t Droop_Forming_Resistive(float P, float Q, float Pref, float Qref, float omegaref, float Vref, float* angle, float* Vd){

	static float deltaF = 0;
	static float olddeltaF = 0;

	deltaF = ((Q-Qref)*_Kq) + omegaref;
	*angle += _TsCoeff*(deltaF + olddeltaF);
    if (*angle > 6.2831853072f){
    	*angle = *angle - 6.2831853072f;
    }
	olddeltaF = deltaF;

	*Vd = (P-Pref) * (-_Kp) + Vref;

	return HAL_OK;
}

