/*
 * Mde_Serial.h
 *
 *  Created on: 27 ene. 2022
 *      Author: adrie
 */

#ifndef MDE_SERIAL_H_
#define MDE_SERIAL_H_

#include "..\Primitivas\PR_ADC.h"
#include "..\Primitivas\PR_Stepper.h"
#include "..\Primitivas\PR_SysTick.h"
#include "..\Primitivas\PR_UART.h"

#define INICIO 0
#define WAIT_SIGNAL 1
#define WAIT_CHAR_FIN 2

#define CHAR_INIT   254
#define CHAR_FIN    253
#define CHAR_STOP   252
#define CHAR_PAUSE  251
#define CHAR_CDIST  250
#define CHAR_SCAN   249
#define CHAR_CAL    248
#define CHAR_MAN    247
#define CHAR_BCK    246
#define CHAR_FWD    245
#define CHAR_BCKSTOP    244
#define CHAR_FWDSTOP    243
#define CHAR_FNSH_FROM_MICRO 242

extern int16_t signal;

void Mde_Serial(int16_t);

#endif /* MDE_SERIAL_H_ */
