/*
 * adc_meas.c
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */
/* Includes ------------------------------------------------------------------*/
#include "adc_meas.h"


/*
 * Helper variable for calculations
 */
static float temp;

/*
 * Coefficients for filters
 */
static float voltageFilterCoeff, currentFilterCoeff;
static const float defaultFilterCoeff = 0.999f; // Default filter size for static values

/*
 * Initial values for offset and DC Link voltage for faster convergence
 */
static float offset = 1.65f;
static float DCLink = 5.0f;


/*
 * PCB Configuration (Difference Amplifier- and Shunt- Resistors and Current OPAMP Gain)
 */
const float R1 = 3300.0f; // R1 in the Difference Amplifier (Voltage Measurement)
const float R2 = 510.0f; // R2 in the Difference Amplifier (Voltage Measurement)
const float RShunt = 0.1f; // Shunt Resistor (Current Measurement)
const float Current_OPAMP_Gain = 100.0f; // Current OPAMP Gain (Current Measurement)

/*
 * Conversion rate for measurements.
 */
static const float ADCConversionRate = 3.3f/4095.0f;
static const float VoltageConversionRate = 1.0f/(R2/R1);
static const float CurrentConversionRate = 1.0f/(RShunt*Current_OPAMP_Gain);


/*
 *  Sets the Filter Coefficients for measurements
 */
uint8_t Voltage_Filter_Length(uint32_t length){
	if(length <= 0){
		voltageFilterCoeff = 0;
	}else{
		voltageFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}
uint8_t Current_Filter_Length(uint32_t length){
	if(length <= 0){
		currentFilterCoeff = 0;
	}else{
		currentFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

/*
 * Conversion from ADC to Direct Voltage.
 */
float ADC_to_Value(uint32_t rawValue){
	return ((float)rawValue * ADCConversionRate);
}

/*
 * Conversion from Direct Voltage to Actual Voltage.
 */
float Voltage_Conversion(float rawValue){
	return (rawValue * VoltageConversionRate);
}

/*
 * Conversion from Direct Voltage to Actual Current.
 */
float Current_Conversion(float rawValue){
	return (rawValue * CurrentConversionRate);
}

/*
 * Measures the Voltage Offset for the rest of the ADC measurements.
 */
float Voltage_Offset(){
	// Measure the ADC value and convert is to the direct voltage.
	temp = ADC_to_Value(ADC_Offset());
	// Filters the value.
	offset = exponential_Filter(defaultFilterCoeff, temp, offset);

	return offset;
}

/*
 * Measures the DC Link voltage. Can be used in control loop.
 */
float Voltage_DCLink(){
	// Measure the ADC value and convert is to the DC Link voltage.
	temp = (ADC_to_Value(ADC_DClink())) * 2.0f;
	// Filters the value.
	DCLink = exponential_Filter(defaultFilterCoeff, temp, DCLink);

	return DCLink;
}

/*
 * meas_Uxx
 * Measures the phase-phase voltage
 * Input:
 * float oldMeas: The old measurement which is used in the filter.
 * Output:
 * float meas_Uxx(): The filtered measurement
 */
float meas_Uab(float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	temp = Voltage_Conversion(ADC_to_Value(ADC_Uab()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}
float meas_Uac(float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	temp = -Voltage_Conversion(ADC_to_Value(ADC_Uac()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}
float meas_Ubc(float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	temp = Voltage_Conversion(ADC_to_Value(ADC_Ubc()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}

/*
 * meas_Ix
 * Measures the phase current
 * Input:
 * float oldMeas: The old measurement which is used in the filter.
 * Output:
 * float meas_Ix(): The filtered measurement
 */
float meas_Ia(float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = -Current_Conversion(ADC_to_Value(ADC_Ia()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}
float meas_Ib(float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = -Current_Conversion(ADC_to_Value(ADC_Ib()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}
float meas_Ic(float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = -Current_Conversion(ADC_to_Value(ADC_Ic()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}






