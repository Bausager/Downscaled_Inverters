/*
 * TimerConfig.c
 *
 *  Created on: Dec 21, 2023
 *      Author: au467674
 */


/* Includes ------------------------------------------------------------------*/
#include "TimerConfig.h"


/*
 * Function:  TIM_freq
 * --------------------
 *	Configures Timer prescaler and auto-reload register for given timer and frequency
 *	Only work with TIM1 and TIM2
 *
 *  uint8_t htim: Which timer is going to be configured
 *  float Hz: Frequency of interrupts for the timer
 *
 *  returns: HAL status
 */
uint8_t TIM_freq(uint8_t htim, float Hz){
// Link: See page 118 for Clock tree
// https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

	/***  Variables ***/
	// Enums for Clock Frequencies
	enum CLK{PCLK1=0, PCLK2=1};
	// PCLK Clock Frequencies
	uint32_t PCLKx_timer_clocks[2] =  {HAL_RCC_GetPCLK1Freq(),  HAL_RCC_GetPCLK2Freq()};
	// Temporary variables
	uint32_t AutoReloadRegister_temp;
	uint16_t Prescaler_temp;
	float F_pwm, temp1, temp2;
	// Temporary variables for output frequency.
	// Needs to be initialized higher than Hz.
	float F_temp = Hz + 1.0f;
	// Max & Min Error Margin
	float Margin_Max = 1.01, Margin_Min = 0.99;

	/*** Timer 1 ***/
	//  See page 142 - RCC APB2 peripheral reset register (RCC_APB2RSTR)
	/*** Timer 1 ***/
	if (htim == 1) {
		// Finds the Timer Clock Frequency.
		if ((RCC->CFGR & RCC_CFGR_PPRE2) != 0) {
			PCLKx_timer_clocks[PCLK2] = PCLKx_timer_clocks[PCLK2]*2.0f;
		}
		// Prescaler 16-bit
		for (uint16_t Prescaler = 65535; Prescaler > 0; Prescaler--) {
			// AutoReloadRegister 16-bit
			for (uint16_t AutoReloadRegister = 0; AutoReloadRegister < 65535; AutoReloadRegister++) {
				// Calculating the Timer Frequency.
				F_pwm = (float)PCLKx_timer_clocks[PCLK2]/(((float)AutoReloadRegister + 1.0f)*((float)Prescaler + 1.0f));
				// Own abs() function.
				if ((F_temp - Hz) < 0) {
					temp1 = (F_temp - Hz) *-1;
				} else {
					temp1 = (F_temp - Hz);
				}

				if ((F_pwm - Hz) < 0) {
					temp2 = (F_pwm - Hz) *-1;
				} else {
					temp2 = (F_pwm - Hz);
				}
				// True if:
				// Calculated Frequency is close to Hz &&
				// If closer to Hz then other calculations with other prescalers.
				if ((F_pwm <= Hz) && (temp1 >= temp2) ) {
					Prescaler_temp = Prescaler;
					AutoReloadRegister_temp = AutoReloadRegister;
					F_temp = F_pwm;
					break;
				}
				// If the frequency overshoots: break.
				else if (F_pwm < Hz) {
					break;
				}
			}
		}
		// If the best found frequency is not within the margin, return: Error
		if ((F_temp > Hz*Margin_Max) || (F_temp < Hz*Margin_Min)) {
			return HAL_ERROR;
		}
		else{
			// Configure Timer with best fit & return: OK
			TIM1->PSC = Prescaler_temp;
			TIM1->ARR = AutoReloadRegister_temp;
			return HAL_OK;
		}
	}
	/*** Timer 2 ***/
	// See page 139 - RCC APB1 peripheral reset register (RCC_APB1RSTR)
	else if (htim == 2) {
		// Finds the Timer Clock Frequency.
		if ((RCC->CFGR & RCC_CFGR_PPRE1) != 0) {
			PCLKx_timer_clocks[PCLK1] = PCLKx_timer_clocks[PCLK1]*2.0f;
		}
		// Prescaler 16-bit
		for (uint16_t Prescaler = 65535; Prescaler > 0; Prescaler--) {
			// AutoReloadRegister 32-bit
			for (uint32_t AutoReloadRegister = 0; AutoReloadRegister < 4294967295; AutoReloadRegister++) {
				// Calculating the Timer Frequency.
				F_pwm = (float)PCLKx_timer_clocks[PCLK1]/(((float)AutoReloadRegister + 1.0f)*((float)Prescaler + 1.0f));
				// Own abs() function.
				if ((F_temp - Hz) < 0) {
					temp1 = (F_temp - Hz) *-1;
				} else {
					temp1 = (F_temp - Hz);
				}
				if ((F_pwm - Hz) < 0) {
					temp2 = (F_pwm - Hz) *-1;
				} else {
					temp2 = (F_pwm - Hz);
				}

				// True if:
				// Calculated Frequency is close to Hz &&
				// If closer to Hz then other calculations with other prescalers.
				if ((F_pwm <= Hz) && (temp1 >= temp2) ) {
					Prescaler_temp = Prescaler;
					AutoReloadRegister_temp = AutoReloadRegister;
					F_temp = F_pwm;
					break;
				}
				// If the frequency overshoots: break.
				else if (F_pwm < Hz) {
					break;
				}
			}
		}

		// If the best found frequency is not within the margin, return: Error
		if ((F_temp > Hz*Margin_Max) || (F_temp < Hz*Margin_Min)) {

			return HAL_ERROR;
		}
		else{
			// Configure Timer with best fit & return: OK
			TIM2->PSC = Prescaler_temp;
			TIM2->ARR = AutoReloadRegister_temp;
			return HAL_OK;
		}
	}
	return HAL_ERROR;
}





