/*
 * transfCalc.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Bausa
 */

#ifndef INC_TRANSFCALC_H_
#define INC_TRANSFCALC_H_

#include <main.h>
#include <math.h>


uint8_t clarkeTrans(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma);
uint8_t clarkeTransInv(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc);

uint8_t simpClarkeTrans(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta);
uint8_t simpClarkeTransInv(float Ualpha, float Ubeta,float* Ua, float* Ub, float* Uc);
uint8_t clarkeTransPower(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma);
uint8_t clarkeTransPowerInv(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc);


uint8_t parkTrans(float Ualpha, float Ubeta, float Ugamma, float Theta, float* Ud, float* Uq, float* Uz);
uint8_t parkTransInv(float Ud, float Uq, float Uz, float Theta, float* Ualpha, float* Ubeta, float* Ugamma);

uint8_t simpParkTrans(float Ualpha, float Ubeta, float Theta, float* Ud, float* Uq);
uint8_t simpParkTransInv(float Ud, float Uq, float Theta, float* Ualpha, float* Ubeta);

uint8_t clarkeParkTrans(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq, float* Uz);
uint8_t clarkeParkTransInv(float Ud, float Uq, float Uz, float Theta, float* Ua, float* Ub, float* Uc);

uint8_t simpClarkeParkTrans(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq);
uint8_t simpClarkeParkTransInv(float Ud, float Uq, float Theta, float* Ua, float* Ub, float* Uc);

#endif /* INC_TRANSFCALC_H_ */
