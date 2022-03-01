/*
 * Mde_Serial.c
 *
 *  Created on: 27 ene. 2022
 *      Author: adrie
 */
#include "Main.h"

int16_t signal;

void Mde_Serial(int16_t dato){
	static uint8_t state=INICIO;
	static int16_t aux=0;

	switch (state){
	case INICIO:
		if(dato==CHAR_INIT)
			state=WAIT_SIGNAL;
		break;
	case WAIT_SIGNAL:
		if (dato<CHAR_FIN){
			state=WAIT_CHAR_FIN;
			aux=dato;
		}else
			state=INICIO;
		break;
	case WAIT_CHAR_FIN:
		if (dato==CHAR_FIN)
			signal=aux;
	    state=INICIO;
		break;
	default :
		state=INICIO;
		aux=0;
		signal=aux;
	}
}
