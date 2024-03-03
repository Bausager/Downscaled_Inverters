/*
 * Inverter.h
 *
 *  Created on: Dec 28, 2023
 *      Author: Bausa
 */

#ifndef INC_INVERTER_H_
#define INC_INVERTER_H_


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h" // For sinf(), cosf


/*** Variables as hardcoded values: ***/
#define PI 3.1415926536f
#define PI2 6.2831853072f
#define PI_THIRDS 1.0471975512f
#define SECTOR 1.0471975512f
#define FULL_CIRCLE 6.2831853072f
#define sector0_angle 1.0471975512f
#define sector1_angle 2.0943951024f
#define sector2_angle 3.1415926536f
#define sector3_angle 4.1887902048f
#define sector4_angle 5.235987756f
#define sector5_angle 6.2831853072f
#define svm_scaling  1.1547005384f
#define MAX_MODULATION_INDEX 0.86602540378443f


/* Puplic function prototypes -----------------------------------------------*/
uint8_t svm_block_init(const uint32_t AutoReloadRegister, const float T_sw);
uint8_t svm_block(const float modulation_idx, const float angle_rad, float* tim_1, float* tim_2, float* tim_3);

float Ud_to_Mi(float DCLinkVoltage, float Ud);


#endif /* INC_INVERTER_H_ */
