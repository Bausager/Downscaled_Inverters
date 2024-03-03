/*
 * control.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Bausa
 */

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "main.h"

uint8_t Droop_Config(float Kp, float Kq, float sampleFreq);
uint8_t Droop_Forming_Resistive(float P, float Q, float Pref, float Qref, float omegaref, float Vref, float* angle, float* Vd);

#endif /* INC_CONTROL_H_ */
