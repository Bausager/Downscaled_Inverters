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

uint8_t transf_abc_to_alphabetagamma(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta, float* Ugamma);
uint8_t transf_alphabetagamma_to_abc(float Ualpha, float Ubeta, float Ugamma,float* Ua, float* Ub, float* Uc);

uint8_t transf_abc_to_alphabeta(float Ua, float Ub, float Uc, float* Ualpha, float* Ubeta);
uint8_t transf_alphabeta_to_abc(float Ualpha, float Ubeta,float* Ua, float* Ub, float* Uc);

uint8_t transf_alphabetagamma_to_dqz(float Ualpha, float Ubeta, float Ugamma, float Theta, float* Ud, float* Uq, float* Uz);
uint8_t transf_dqz_to_alphabetagamma(float Ud, float Uq, float Uz, float Theta, float* Ualpha, float* Ubeta, float* Ugamma);

uint8_t transf_alphabeta_to_dq(float Ualpha, float Ubeta, float Theta, float* Ud, float* Uq);
uint8_t transf_dq_to_alphabeta(float Ud, float Uq, float Theta, float* Ualpha, float* Ubeta);


uint8_t transf_abc_to_dqz(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq, float* Uz);
uint8_t transf_dqz_to_abc(float Ud, float Uq, float Uz, float Theta, float* Ua, float* Ub, float* Uc);
uint8_t transf_abc_to_dq(float Ua, float Ub, float Uc, float Theta, float* Ud, float* Uq);
uint8_t transf_dq_to_abc(float Ud, float Uq, float Theta, float* Ua, float* Ub, float* Uc);


#endif /* INC_TRANSFCALC_H_ */
