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
#include "transfCalc.h"
#include "math.h"
/* Puplic variables ---------------------------------------------------------*/

uint8_t dqPLL(float Ua, float Ub, float, Uc, float ThetaIn, float* ThetaOut, float* Ud);


#endif /* INC_PPL_H_ */
