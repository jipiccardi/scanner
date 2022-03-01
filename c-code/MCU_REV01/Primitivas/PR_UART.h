/*
 * PR_UART.h
 *
 *  Created on: 25 oct. 2021
 *      Author: chor
 */

#ifndef PR_UART_H_
#define PR_UART_H_

#include "C:\Users\adrie\Documents\MCUXpressoIDE_11.4.0_6224\workspace\TPO\Drivers\LPC845.h"
#include "..\Drivers\DR_UART.h"
#include "..\src\Mde_Scan.h"


extern uint16_t flag_TX;

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


void TransmitirDato ( uint16_t dato);
void send_FIN();
int16_t RecibirSerie ( void );

#endif /* PR_UART_H_ */
