/*
 * transfCalc.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Bausa
 */
#include "transfCalc.h"

static float cosTemp, sinTemp, temp1, temp2, temp3;



uint8_t transf_abc_to_alphabetagamma(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma){
	*Ualpha = (0.66666f*Ua) + (-0.33333f*Ub) + (-0.33333f*Uc);
	*Ubeta = (0.57735f*Ub) + (-0.57735f*Uc);
	*Ugamma = (0.33333f*Ua) + (0.33333f*Ub) + (0.33333f*Uc);

	return HAL_OK;
}
uint8_t transf_alphabetagamma_to_abc(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc){
	*Ua = Ualpha + Ugamma;
	*Ub = (-0.5f*Ualpha) + (0.86602f*Ubeta) + (Ugamma);
	*Uc = (-0.5f*Ualpha) + (-0.86602f*Ubeta) + (Ugamma);
	return HAL_OK;
}

uint8_t transf_abc_to_alphabeta(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta){
	*Ualpha = (0.66666f*Ua) + (-0.33333f*Ub) + (-0.33333f*Uc);
	*Ubeta = (0.57735f*Ub) + (-0.57735f*Uc);
	//*Ugamma = (0.33333f*Ua) + (0.33333f*Ub) + (0.33333f*Uc);

	return HAL_OK;
}
uint8_t transf_alphabeta_to_abc(float Ualpha, float Ubeta,float* Ua, float* Ub, float* Uc){
	*Ua = Ualpha;
	*Ub = (-0.5f*Ualpha) + (0.86602f*Ubeta);
	*Uc = (-0.5f*Ualpha) + (-0.86602f*Ubeta);
	return HAL_OK;
}

uint8_t transf_alphabetagamma_to_dqz(float Ualpha, float Ubeta, float Ugamma, float Theta, float* Ud, float* Uq, float* Uz){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ud = (cosTemp*Ualpha) + (sinTemp*Ubeta);
	*Uq = (-sinTemp*Ualpha) + (cosTemp*Ubeta);
	*Uz = Ugamma;

	return HAL_OK;
}
uint8_t transf_dqz_to_alphabetagamma(float Ud, float Uq, float Uz, float Theta, float* Ualpha, float* Ubeta, float* Ugamma){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ualpha = (cosTemp*Ud) + (-sinTemp*Uq);
	*Ubeta = (sinTemp*Ud) + (cosTemp*Uq);
	*Ugamma = Uz;

	return HAL_OK;
}

uint8_t transf_alphabeta_to_dq(float Ualpha, float Ubeta, float Theta, float* Ud, float* Uq){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ud = (cosTemp*Ualpha) + (sinTemp*Ubeta);
	*Uq = (-sinTemp*Ualpha) + (cosTemp*Ubeta);

	return HAL_OK;
}
uint8_t transf_dq_to_alphabeta(float Ud, float Uq, float Theta, float* Ualpha, float* Ubeta){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ualpha = (cosTemp*Ud) + (-sinTemp*Uq);
	*Ubeta = (sinTemp*Ud) + (cosTemp*Uq);

	return HAL_OK;
}



uint8_t transf_abc_to_dqz(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq, float* Uz){
	transf_abc_to_alphabetagamma(Ua, Ub, Uc, &temp1, &temp2, &temp3);
	transf_alphabetagamma_to_dqz(temp1, temp2, temp3, Theta, Ud, Uq, Uz);

	return HAL_OK;
}
uint8_t transf_dqz_to_abc(float Ud, float Uq, float Uz, float Theta, float* Ua, float* Ub, float* Uc){
	transf_dqz_to_alphabetagamma(Ud, Uq, Uz, Theta, &temp1, &temp2, &temp3);
	transf_alphabetagamma_to_abc(temp1, temp2, temp3, Ua, Ub, Uc);

	return HAL_OK;
}
uint8_t transf_abc_to_dq(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq){
	transf_abc_to_alphabeta(Ua, Ub, Uc, &temp1, &temp2);
	transf_alphabeta_to_dq(temp1, temp2, Theta, Ud, Uq);

	return HAL_OK;
}
uint8_t transf_dq_to_abc(float Ud, float Uq, float Theta, float* Ua, float* Ub, float* Uc){
	transf_dq_to_alphabeta(Ud, Uq, Theta, &temp1, &temp2);
	transf_alphabeta_to_abc(temp1, temp2, Ua, Ub, Uc);

	return HAL_OK;
}


