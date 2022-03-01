/*
 * DR_UART.c
 *
 *  Created on: 20 oct. 2021
 *      Author: chor
 */
#include "DR_UART.h"

uint8_t buf_tx[TAM_TX];
int16_t buf_rx[TAM_RX];

uint16_t in_tx=0,out_tx=0,in_rx,out_rx;
uint8_t flag_tx_wait=0;

uint8_t primerDato = 1;

void UART0_Init(void)
{
	// HABILITO LA UART0
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 14);

	//Reseteo la UART0:
	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);

	//Habilito el CLK a la SWM:
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);

	// CONFIGURO LA MATRIX TX0 en P0.25	y RX0 en P0.24
	PINASSIGN0 &= ~(0x0000FFFFF);
	PINASSIGN0 = (25 << 0) | (24 << 8);

	// CONFIGURACION GENERAL
	USART0->CFG = 	(0 << 0)		// 0=DISABLE 1=ENABLE
				| (1 << 2)		// 0=7BITS 1=8BITS 2=9BITS
				| (0 << 4)		// 0=NOPARITY 2=PAR 3=IMPAR
				| (0 << 6)		// 0=1BITSTOP 1=2BITSTOP
				| (0 << 9)		// 0=NOFLOWCONTROL 1=FLOWCONTROL
				| (0 << 11);	// 0=ASINCRONICA 1=SINCRONICA

	// CONFIGURACION INTERRUPCIONES
	USART0->INTENSET = (1 << 0);	//RX

	// CONFIGURACION DEL BAUDRATE
	UART0CLKSEL = 0; //CLK = FRO = 30MHz
	USART0->BRG = (FREQ_PRINCIPAL / (BAUDRATE* 16));

	//Habilito interrupcion USART0 en el NVIC
	ISER0 |= (1 << 3);

	// ENABLE LA UART
	USART0->CFG |= 1;

	return;
}


void UART0_IRQHandler (void)
{
	uint32_t stat = USART0->STAT;
	int8_t aux;

    // CASO RECEPCION
	if(stat & (1 << 0))
	{
		PushRx(USART0->RXDAT);
	}

	//CASO TRANSMISION
	if(stat & (1 << 2))
	{
		//Si hay algun dato mas por enviar lo mando, sino deshabilito las interrupciones:
		aux = PopTx();

		if ( aux != -1 )
			USART0->TXDAT = aux;
		else
			USART0->INTENCLR = 1<<2;
	}

}

int16_t PopTx ( void )
{
	int16_t retorno = -1;

	if ( out_tx != in_tx )
	{
		retorno = buf_tx[out_tx];
		out_tx++;
		out_tx%=TAM_TX;
	}

	return retorno;
}

int16_t PopRx ( void )
{
	int16_t retorno = -1;

	if ( out_rx != in_rx )
	{
		retorno = buf_rx[out_rx];
		out_rx++;
		out_rx%=TAM_RX;
	}

	return retorno;

}

void PushTx ( uint8_t dato )
{
	buf_tx[in_tx] = dato;
	in_tx++;
	in_tx%= TAM_TX;

	//Cuando pongo un dato en el buffer habilito la interrupcion para que me avise cuando se envio:
	USART0->INTENSET |= 1<<2;
}

void PushRx ( uint8_t dato )
{
	buf_rx[in_rx] = dato;
	in_rx++;
	in_rx%= TAM_RX;

}

