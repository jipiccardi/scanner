/*
 * Mde_Fwd_Bck.c
 *
 *  Created on: 29 ene. 2022
 *      Author: adrie
 */

#include "Main.h"

void Mde_Fwd_Bck(uint8_t dir){
	static uint8_t state=INICIO;
	static uint8_t direction;

	if (flag_stop){
			state=INICIO;
			flag_stop=FALSE;
	}
	switch (state){
	case INICIO:
		direction=dir;
		if (direction==FWD)
			Motor0_DOWN(-2048);
		else if (direction==BCK)
			Motor0_UP(2048);
		signal=0;
		state=WAIT_CHAR_STOP;
		break;
	case WAIT_CHAR_STOP:
		if (signal==CHAR_STOP){
			flag_fin=TRUE; //NO_MODE
			signal=0;
			state=INICIO;
		}else if (flag_stepper==255){
			if (direction==FWD)
				Motor0_DOWN(-2048);
			else if (direction==BCK)
				Motor0_UP(2048);
		}break;
	default:
		signal=INICIO;
	}
}
