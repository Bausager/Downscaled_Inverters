/*
 * transfCalc.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Bausa
 */
#include "transfCalc.h"

static float cosTemp, sinTemp, temp1, temp2, temp3;

static const float Const1 = (2.0f/3.0f);
static const float Const2 = (sqrtf(3.0f)/2.0f);
static const float Const3 = (1.0f/sqrtf(2.0f));

static const float Const4 = Const1*0.5f;
static const float Const5 = Const1*(sqrtf(3.0f)/2.0f);

static const float Const6 = (3.0f/2.0f);
static const float Const7 = Const6 *Const1;
static const float Const8 = Const6 * (1.0f/3.0f);
static const float Const9 = Const6*(sqrtf(3.0f)/3.0f);

static const float Const10 = sqrtf(2.0f/3.0f);
static const float Const11 = Const10*0.5f;
static const float Const12 = Const10*Const2;
static const float Const13 = Const10*Const3;





uint8_t clarkeTrans(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma){
	*Ualpha = (Const1*Ua) + (-Const4*Ub) + (-Const4*Uc);
	*Ubeta = (Const5*Ub) + (-Const5*Uc);
	*Ugamma = (Const4*Ua) + (Const4*Ub) + (Const4*Uc);

	return HAL_OK;
}
uint8_t clarkeTransInv(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc){
	*Ua = Ualpha + Ugamma;
	*Ub = (-0.5f*Ualpha) + (Const2*Ubeta) + (Ugamma);
	*Uc = (-0.5f*Ualpha) + (-Const2*Ubeta) + (Ugamma);
	return HAL_OK;
}

uint8_t simpClarkeTrans(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta){
	*Ualpha = (Const1*Ua) + (-Const4*Ub) + (-Const4*Uc);
	*Ubeta = (Const5*Ub) + (-Const5*Uc);

	return HAL_OK;
}
uint8_t simpClarkeTransInv(float Ualpha, float Ubeta,float* Ua, float* Ub, float* Uc){
	*Ua = Const7*Ualpha;
	*Ub = (-Const8*Ualpha) + (Const9*Ubeta);
	*Uc = (-Const8*Ualpha) + (-Const9*Ubeta);
	return HAL_OK;
}

uint8_t clarkeTransPower(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma){
	*Ualpha = (Const10*Ua) + (-Const11*Ub) + (-Const11*Uc);
	*Ubeta = (Const12*Ub) + (-Const12*Uc);
	*Ugamma = (Const13*Ua) + (Const13*Ub) + (Const13*Uc);

	return HAL_OK;
}
uint8_t clarkeTransPowerInv(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc){
	*Ua = (Const10*Ualpha) + (Const13*Ugamma);
	*Ub = (-Const11*Ualpha) + (Const12*Ubeta) + (Const13*Ugamma);
	*Uc = (-Const11*Ualpha) + (-Const12*Ubeta) + (Const13* Ugamma);
	return HAL_OK;
}


uint8_t parkTrans(float Ualpha, float Ubeta, float Ugamma, float Theta, float* Ud, float* Uq, float* Uz){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ud = (cosTemp*Ualpha) + (sinTemp*Ubeta);
	*Uq = (-sinTemp*Ualpha) + (cosTemp*Ubeta);
	*Uz = Ugamma;

	return HAL_OK;
}
uint8_t parkTransInv(float Ud, float Uq, float Uz, float Theta, float* Ualpha, float* Ubeta, float* Ugamma){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ualpha = (cosTemp*Ud) + (-sinTemp*Uq);
	*Ubeta = (sinTemp*Ud) + (cosTemp*Uq);
	*Ugamma = Uz;

	return HAL_OK;
}


uint8_t simpParkTrans(float Ualpha, float Ubeta, float Theta, float* Ud, float* Uq){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ud = (cosTemp*Ualpha) + (sinTemp*Ubeta);
	*Uq = (-sinTemp*Ualpha) + (cosTemp*Ubeta);

	return HAL_OK;
}
uint8_t simpParkTransInv(float Ud, float Uq, float Theta, float* Ualpha, float* Ubeta){

	cosTemp = cosf(Theta);
	sinTemp = sinf(Theta);

	*Ualpha = (cosTemp*Ud) + (-sinTemp*Uq);
	*Ubeta = (sinTemp*Ud) + (cosTemp*Uq);

	return HAL_OK;
}

uint8_t clarkeParkTrans(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq, float* Uz){
	clarkeTrans(Ua, Ub, Uc, &temp1, &temp2, &temp3);
	parkTrans(temp1, temp2, temp3, Theta, Ud, Uq, Uz);

	return HAL_OK;
}

uint8_t clarkeParkTransInv(float Ud, float Uq, float Uz, float Theta, float* Ua, float* Ub, float* Uc){
	parkTransInv(Ud, Uq, Uz, Theta, &temp1, &temp2, &temp3);
	clarkeTransInv(temp1, temp2, temp3, Ua, Ub, Uc);

	return HAL_OK;
}

uint8_t simpClarkeParkTrans(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq){
	simpClarkeTrans(Ua, Ub, Uc, &temp1, &temp2);
	simpParkTrans(temp1, temp2, Theta, Ud, Uq);

	return HAL_OK;
}

uint8_t simpClarkeParkTransInv(float Ud, float Uq, float Theta, float* Ua, float* Ub, float* Uc){
	simpParkTransInv(Ud, Uq, Theta, &temp1, &temp2);
	simpClarkeTransInv(temp1, temp2, Ua, Ub, Uc);

	return HAL_OK;
}


