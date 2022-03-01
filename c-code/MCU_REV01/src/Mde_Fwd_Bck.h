/*
 * Mde_Fwd_Bck.h
 *
 *  Created on: 29 ene. 2022
 *      Author: adrie
 */

#ifndef MDE_FWD_BCK_H_
#define MDE_FWD_BCK_H_

#include "..\Primitivas\PR_ADC.h"
#include "..\Primitivas\PR_Stepper.h"
#include "..\Primitivas\PR_SysTick.h"
#include "..\Primitivas\PR_UART.h"
#include "Main.h"
#include "Mde_Serial.h"

#define INICIO 0
#define WAIT_CHAR_STOP 1

#define BCK 0
#define FWD 1

void Mde_Fwd_Bck(uint8_t );

#endif /* MDE_FWD_BCK_H_ */
