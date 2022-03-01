/*
 * PR_UART.c
 *
 *  Created on: 25 oct. 2021
 *      Author: chor
 */

#include "PR_UART.h"

 uint16_t flag_TX=0;

void TransmitirDato ( uint16_t dato)
{
	PushTx(dato/1000+48);
	dato%=1000;
	PushTx(dato/100+48);
	dato%=100;
	PushTx(dato/10+48);
	dato%=10;
	PushTx(dato+48);
	PushTx(10);
}

void send_FIN()
{
	PushTx(CHAR_INIT);
	PushTx(CHAR_STOP);
	PushTx(CHAR_FIN);
}

int16_t RecibirSerie ( void )
{
	return PopRx();
}

