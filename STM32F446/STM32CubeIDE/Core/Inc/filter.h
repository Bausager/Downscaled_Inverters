/*
 * filter.h
 *
 *  Created on: Feb 13, 2024
 *      Author: au467674
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Puplic variables ---------------------------------------------------------*/


float exponentialFilter(float alpha, float avg, float value);


#endif /* INC_FILTER_H_ */
