/*
 * PPL.h
 *
 *  Created on: Feb 16, 2024
 *      Author: Bausa
 */

#ifndef INC_PLL_H_
#define INC_PLL_H_
/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include "transfCalc.h" // for transf_abc_to_dq()


uint8_t dqPLL_Config(float nom_f, float sampleFreq);
uint8_t dqPLL(float Ua, float Ub, float Uc, float* Theta, float* Ud);


#endif /* INC_PPL_H_ */
