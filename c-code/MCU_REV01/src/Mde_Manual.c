/*
 * Mde_Manual.c
 *
 *  Created on: 28 ene. 2022
 *      Author: adrie
 */
#include "Main.h"

void Mde_Manual(void){
	static uint8_t state=0;
	static int16_t axis_steps;
	if (flag_stop){
		state=WAIT_PARAMETER_MOVE;
		flag_stop=FALSE;
	}
	switch (state){
	case WAIT_PARAMETER_MOVE:
		if(signal){
			axis_steps=(2048*signal/8);
			signal=0;
			if (axis_steps>0)
			Motor0_UP(axis_steps);
			else Motor0_DOWN(axis_steps);
			state=ROT;
		}break;
	case ROT:
		if (flag_stepper==255){                     //Cuando termina el movimiento
			send_FIN();
			flag_fin=TRUE; //NO_MODE
			state=WAIT_PARAMETER_MOVE;
		}break;
	default:
		state=ROT;
		flag_stepper==255;
	}
}
