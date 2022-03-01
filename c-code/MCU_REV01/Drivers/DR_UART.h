/*
 * DR_UART.h
 *
 *  Created on: 20 oct. 2021
 *      Author: chor
 */

#ifndef DR_UART_H_
#define DR_UART_H_

#include "LPC845.h"

extern uint8_t buf_tx[];
extern int16_t buf_rx[];

extern uint16_t in_tx,out_tx,in_rx,out_rx;


#define	TAM_TX	10001
#define	TAM_RX	32

#define FREQ_PRINCIPAL	30000000U
#define BAUDRATE		128000

void UART0_Init( void );
void UART0_IRQHandler (void);

void PushTx(uint8_t );
void PushRx(uint8_t );
int16_t PopRx(void);
int16_t PopTx(void);


#endif /* DR_UART_H_ */
