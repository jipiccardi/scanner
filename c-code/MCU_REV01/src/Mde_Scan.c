/*
 * Mde_Scan.c
 *
 *  Created on: 10 dic. 2021
 *      Author: adrie
 */
#include "Main.h"
uint16_t flag_rot;
uint16_t flag_height;

void Mde_Scan(){
	static uint8_t state=0;
	static uint16_t full_rot=0;
	static int16_t angle_steps,axis_steps;
	uint16_t dato;

	if (flag_stop){
		state=INICIO;
		flag_stop=FALSE;
	}
	switch (state){
	case INICIO:
		Enb_ADC(MEDxP);
		state=WAIT_PARAMETER_A;
		break;
	case WAIT_PARAMETER_A:
		if(signal){
			axis_steps=(2048*signal/80); //Como no puedo enviar numero con decimal multiplico por 10
			//flag_height=HEIGHT/signal;
			flag_height=3;
			signal=0;
			state=WAIT_PARAMETER_B;
		}
		break;
	case WAIT_PARAMETER_B:
		if(signal){
			angle_steps=2048*signal/360;
			full_rot=2048/angle_steps;
			flag_rot=full_rot;//Calculo la cantidad de angulos que medirá por vuelta
			state=MED;
		}
		break;
	case MED:
		if ((dato=LecturaADC())!=((uint16_t)-1)){
			TransmitirDato(dato);
			flag_TX--;
		}
		if (flag_TX==0){
			Motor1_Clockwise(angle_steps);
			state=ROT;
		}break;
	case ROT:
		if (flag_stepper==255){                     //Cuando termina la rotación
			flag_stepper=254;                       //Deselecciono el motor
			TimerStart(2,300,T_Wait_Handler,MILI);   //Inicio un Timer que me deja estatico por 40 ms la pieza
		}if(flag_T_Wait){
			flag_T_Wait=0;
			flag_rot--;
			if (flag_rot){
				Enb_ADC(MEDxP);
				state=MED;
			}else{
				flag_rot=full_rot;
				Motor0_UP(axis_steps);
				state=Z_MOVE;
			}
		}break;
	case Z_MOVE:
		if (flag_stepper==255){
			flag_stepper=254;
			TimerStart(2,2,T_Wait_Handler,SEC);
		}if(flag_T_Wait){
			flag_T_Wait=0;
			flag_height--;
			if (flag_height){
				Enb_ADC(MEDxP);
				state=MED;

			}else{
				send_FIN();
				flag_fin=TRUE; //NO_MODE
				state=INICIO;
			}
		}
	break;
	default:
		state=Z_MOVE;
		flag_stepper=255;
		flag_height=0;
	}
}
