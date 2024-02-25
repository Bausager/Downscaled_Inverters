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

uint8_t transf_abc_to_alphabetagamma(const float Ua, const float Ub, const float Uc, float* Ualpha, float* Ubeta, float* Ugamma);
uint8_t transf_alphabetagamma_to_abc(const float Ualpha, const float Ubeta, const float Ugamma, float* Ua, float* Ub, float* Uc);

uint8_t transf_abc_to_alphabeta(const float Ua, const float Ub, const float Uc, float* Ualpha, float* Ubeta);
uint8_t transf_alphabeta_to_abc(const float Ualpha, const float Ubeta, float* Ua, float* Ub, float* Uc);

uint8_t transf_alphabetagamma_to_dqz(const float Ualpha, const float Ubeta, const float Ugamma, float Theta, float* Ud, float* Uq, float* Uz);
uint8_t transf_dqz_to_alphabetagamma(const float Ud, const float Uq, const float Uz, const float Theta, float* Ualpha, float* Ubeta, float* Ugamma);

uint8_t transf_alphabeta_to_dq(const float Ualpha, const float Ubeta, const float Theta, float* Ud, float* Uq);
uint8_t transf_dq_to_alphabeta(const float Ud, const float Uq, const float Theta, float* Ualpha, float* Ubeta);


uint8_t transf_abc_to_dqz(const float Ua, const float Ub, const float Uc, const float Theta, float* Ud, float* Uq, float* Uz);
uint8_t transf_dqz_to_abc(const float Ud, const float Uq, const float Uz, const float Theta, float* Ua, float* Ub, float* Uc);
uint8_t transf_abc_to_dq(const float Ua, const float Ub, const float Uc, const float Theta, float* Ud, float* Uq);
uint8_t transf_dq_to_abc(const float Ud, const float Uq, const float Theta, float* Ua, float* Ub, float* Uc);


#endif /* INC_TRANSFCALC_H_ */
