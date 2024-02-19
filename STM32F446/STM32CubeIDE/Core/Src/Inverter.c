/*
 * Inverter.c
 *
 *  Created on: Dec 28, 2023
 *      Author: Bausa
 */


/* Includes ------------------------------------------------------------------*/
#include "Inverter.h"


/* Puplic variables ---------------------------------------------------------*/
static float svm_period_scaler, svm_T_sw;
static uint32_t svm_AutoReloadRegister;



uint8_t svm_block_init(uint32_t AutoReloadRegister, float Freq){
	svm_T_sw = 1.0f/Freq;
	svm_period_scaler = AutoReloadRegister/svm_T_sw;
	svm_AutoReloadRegister = AutoReloadRegister;
	return HAL_OK;
}

uint8_t svm_block(float modulation_idx, float angle_rad, float* tim_1, float* tim_2, float* tim_3){

	float svm_angle = angle_rad - (floorf(angle_rad/FULL_CIRCLE)*FULL_CIRCLE);
	float svm_angle_in_sector = svm_angle - floorf(svm_angle/SECTOR)*SECTOR;
	float svm_sector =  floorf(svm_angle/SECTOR);

    if ((svm_sector == 1 ) || (svm_sector == 3) || (svm_sector == 5))
    {
        svm_angle_in_sector = SECTOR - svm_angle_in_sector;
    }

    float t_a = svm_scaling * modulation_idx * svm_T_sw * sinf((PI_THIRDS - svm_angle_in_sector)) ;
    float t_b = svm_scaling * modulation_idx * svm_T_sw * sinf(svm_angle_in_sector) ;
    // Third harmonic injection
    float t_0 = svm_T_sw*0.5f*(1.0f - (1.2732395447f)*modulation_idx*(cosf(svm_angle_in_sector) - (0.1666666667f)*cosf(3.0f*svm_angle_in_sector)));

	float t_1, t_2, t_3;
    if(svm_angle < sector0_angle) //sector 0 - state 4
    {    // sector0 => pwma = t0, pwmb = ta, pwmc = tb
        t_1 = t_0;
        t_2 = t_a + t_0;
        t_3 = t_b + t_a + t_0;
    }
    else if(svm_angle < sector1_angle) //sector 1 - state 6
    {
        t_1 = t_a + t_0;
        t_2 = t_0;
        t_3 = t_b + t_a + t_0;
    }
    else if(svm_angle < sector2_angle) //sector 2 - state 2
    {
        t_1 = t_a + t_b + t_0;
        t_2 = t_0;
        t_3 = t_a + t_0;
    }
    else if(svm_angle < sector3_angle) //sector 3 - state 3
    {
        t_1 = t_a + t_b + t_0;
        t_2 = t_a + t_0;
        t_3 = t_0;
    }
    else if(svm_angle < sector4_angle) //sector 4 - state 1
    {
        t_1 = t_a + t_0;
        t_2 = t_a + t_b + t_0;
        t_3 = t_0;
    }
    else if(svm_angle < sector5_angle)//sector 5 - state 5
    {
        t_1 = t_0;
        t_2 = t_a + t_b + t_0;
        t_3 = t_a + t_0;
    }
    else{
    	return HAL_ERROR;
    }

	t_1 = floorf((t_1)*(svm_period_scaler) + 0.5f); // Update compare values
	t_2 = floorf((t_2)*(svm_period_scaler) + 0.5f); // Update compare values
	t_3 = floorf((t_3)*(svm_period_scaler) + 0.5f); // Update compare values

    if(t_1 > svm_AutoReloadRegister){
    	t_1 = svm_AutoReloadRegister;
    }
    else if (t_1 < 0){
    	t_1 = 0;
    }
    if (t_2 > svm_AutoReloadRegister){
    	t_2 = svm_AutoReloadRegister;
    }
    else if (t_2 < 0){
    	t_2 = 0;
    }
    if (t_3 > svm_AutoReloadRegister){
    	t_3 = svm_AutoReloadRegister;
    }
    else if (t_3 < 0){
    	t_3 = 0;
    }
    *tim_1 = t_1;
    *tim_2 = t_2;
    *tim_3 = t_3;
	return HAL_OK;
}





