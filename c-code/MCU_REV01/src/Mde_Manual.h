/*
 * Mde_Manual.h
 *
 *  Created on: 29 ene. 2022
 *      Author: adrie
 */

#ifndef MDE_MANUAL_H_
#define MDE_MANUAL_H_

#include "..\Primitivas\PR_ADC.h"
#include "..\Primitivas\PR_Stepper.h"
#include "..\Primitivas\PR_SysTick.h"
#include "..\Primitivas\PR_UART.h"

#include "Mde_Serial.h"

#define WAIT_PARAMETER_MOVE 0



void Mde_Manual(void);

#endif /* MDE_MANUAL_H_ */
