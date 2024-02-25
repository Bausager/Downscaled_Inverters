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
static const float defaultFilterCoeff = 0.999f; // Default filter size for DC values

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
static const float CurrentConversionRate = -1.0f/(RShunt*Current_OPAMP_Gain); // It's negative because of the OPAMP orientation.


/*
 * Function:  Voltage_Filter_Length
 * --------------------------------
 *	Computes an filter coefficient that's between: [0,1]
 *
 *  const uint32_t length: the sample length of the filter coefficient
 *
 *  returns: HAL status
 */
uint8_t Voltage_Filter_Length(const uint32_t length){
	if(length <= 0){
		voltageFilterCoeff = 0;
	}else{
		voltageFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

/*
 * Function:  Current_Filter_Length
 * --------------------------------
 *	Computes an filter coefficient that's between: [0,1]
 *
 *  const uint32_t length: the sample length of the filter coefficient
 *
 *  returns: HAL status
 */
uint8_t Current_Filter_Length(const uint32_t length){
	if(length <= 0){
		currentFilterCoeff = 0;
	}else{
		currentFilterCoeff = 1.0f - (1.0f/length);
	}

	return HAL_OK;
}

/*
 * Function:  ADC_to_Value
 * -----------------------
 *	Converts the ADC integer to the actual voltage on the pin
 *
 *  const uint32_t rawValue: The raw integer value the ADC
 *
 *  returns: Voltage on the pin used for the ADC
 */
float ADC_to_Value(const uint32_t rawValue){
	return ((float)rawValue * ADCConversionRate);
}

/*
 * Function:  Voltage_Conversion
 * ------------------------------
 *	Converts the voltage in the pin to the correct voltage difference between the phases
 *
 *  const float rawValue: Voltage on the pin.
 *
 *  returns: Actual voltage between the phases.
 */
float Voltage_Conversion(const float rawValue){
	return (rawValue * VoltageConversionRate);
}

/*
 * Function:  Current_Conversion
 * ------------------------------
 *	Converts the voltage in the pin to the correct line current
 *
 *  const float rawValue: Voltage on the pin.
 *
 *  returns: Actual current on the phase.
 */
float Current_Conversion(const float rawValue){
	return (rawValue * CurrentConversionRate);
}

/*
 * Function:  Voltage_Offset
 * --------------------------
 *	Measures the voltage offset for the AC value conversions, filters it, stores it locally and also returns it if needed
 *
 *  returns: The voltage offset for every AC measurement
 */
float Voltage_Offset(){
	// Measure the ADC value and convert is to the direct voltage.
	temp = ADC_to_Value(ADC_Offset());
	// Filters the value.
	offset = exponential_Filter(defaultFilterCoeff, temp, offset);

	return offset;
}

/*
 * Function:  Voltage_DCLink
 * --------------------------
 *	Measures the DC Link voltage, filters it, stores it locally and also returns it if needed
 *
 *  returns: The DC Link voltage
 */
float Voltage_DCLink(){
	// Measure the ADC value and convert is to the DC Link voltage.
	temp = (ADC_to_Value(ADC_DClink())) * 2.0f;
	// Filters the value.
	DCLink = exponential_Filter(defaultFilterCoeff, temp, DCLink);

	return DCLink;
}

/*
 * Function:  meas_Uab
 * -------------------
 *	Measures, converts and filters the line-line voltage for Phase A-B
 *
 *  const float oldMeas: Variable for the filtered voltage
 *
 *  returns: The filtered line-line voltage for Phase A-B
 */
float meas_Uab(const float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	temp = Voltage_Conversion(ADC_to_Value(ADC_Uab()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}

/*
 * Function:  meas_Ubc
 * -------------------
 *	Measures, converts and filters the line-line voltage for Phase B-C
 *
 *  const float oldMeas: Variable for the filtered voltage
 *
 *  returns: The filtered line-line voltage for Phase B-C
 */
float meas_Ubc(const float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	temp = Voltage_Conversion(ADC_to_Value(ADC_Ubc()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}

/*
 * Function:  meas_Uac
 * -------------------
 *	Measures, converts and filters the line-line voltage for Phase C-A
 *
 *  const float oldMeas: Variable for the filtered voltage
 *
 *  returns: The filtered line-line voltage for Phase C-A
 */
float meas_Uca(const float oldMeas){
	// Measure the ADC value and convert is to the phase voltage.
	// The measured voltage is from A-C not C-A, but converted to C-A because if the general phase convention.
	temp = -Voltage_Conversion(ADC_to_Value(ADC_Uac()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(voltageFilterCoeff, temp, oldMeas);
}

/*
 * Function:  meas_Ia
 * -------------------
 *	Measures, converts and filters the line current for Phase A
 *
 *  const float oldMeas: Variable for the filtered current
 *
 *  returns: The filtered line current for Phase A
 */
float meas_Ia(const float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = Current_Conversion(ADC_to_Value(ADC_Ia()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}

/*
 * Function:  meas_Ib
 * -------------------
 *	Measures, converts and filters the line current for Phase B
 *
 *  const float oldMeas: Variable for the filtered current
 *
 *  returns: The filtered line current for Phase B
 */
float meas_Ib(const float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = Current_Conversion(ADC_to_Value(ADC_Ib()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}

/*
 * Function:  meas_Ic
 * -------------------
 *	Measures, converts and filters the line current for Phase C
 *
 *  const float oldMeas: Variable for the filtered current
 *
 *  returns: The filtered line current for Phase C
 */
float meas_Ic(const float oldMeas){
	// Measure the ADC value and convert is to the phase current.
	temp = Current_Conversion(ADC_to_Value(ADC_Ic()) - offset);
	// Filter and returns the voltage.
	return exponential_Filter(currentFilterCoeff, temp, oldMeas);
}






