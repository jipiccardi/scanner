/*
 * DR_Stepper.c
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#include "DR_Stepper.h"

int32_t pasos_M0=0;
int32_t pasos_M1=0;
uint8_t flag_stepper=-1; // 0=Motor0 1=Motor1

void InitStepper(void){

	for (uint8_t i=16;i<24;i++)
		SetDIR(0,i,1);

	SetPINMODE_OUT(IOCON_INDEX_PIO0_16,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_17,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_18,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_19,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_20,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_21,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_22,0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_23,0);

	for (uint8_t i=16;i<24;i++)
		SetPIN(0,i,LOW);
}

void M0_ClockWise_FullStep(void){

	static uint8_t estado=0,next_estado=0;
	switch (estado){
	case A:
		SetPIN(COIL0_3,LOW);
		SetPIN(COIL0_0,HIGH);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		estado=B;
		pasos_M0--;
		if ((pasos_M0)==1){
			estado=FIN;
			next_estado=B;
		}
		break;
	case B:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,HIGH);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,LOW);
		estado=C;
		pasos_M0--;

		if ((pasos_M0)==1){
			estado=FIN;
			next_estado=C;
		}
		break;
	case C:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,HIGH);
		SetPIN(COIL0_3,LOW);
		estado=D;
		pasos_M0--;
		if ((pasos_M0)==1){
			estado=FIN;
			next_estado=D;
		}
		break;
	case D:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,HIGH);
		pasos_M0--;
		estado=A;
		if ((pasos_M0)==1){
			estado=FIN;
			next_estado=A;
		}

		break;

	case FIN:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,LOW);
		flag_stepper=-1;
		estado=next_estado;
		break;
	}
}

void M0_Counter_ClockWise_FullStep(void){

	static uint8_t estado=0,next_estado=0;
	static uint8_t flag=0,count=0;

	switch (estado){
	case A:
		SetPIN(COIL0_0,HIGH);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,LOW);
		estado=B;
		pasos_M0++;
		if ((pasos_M0)==-1){
			estado=FIN;
			next_estado=B;
		}
		break;
	case B:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,HIGH);
		estado=C;
		pasos_M0++;
		if ((pasos_M0)==-1){
			estado=FIN;
			next_estado=C;
		}
		break;
	case C:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,HIGH);
		SetPIN(COIL0_3,LOW);
		estado=D;
		pasos_M0++;
		if ((pasos_M0)==-1){
			estado=FIN;
			next_estado=D;
		}
		break;
	case D:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,HIGH);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,LOW);
		estado=A;
		pasos_M0++;
		if ((pasos_M0)==-1){
			estado=FIN;
			next_estado=A;
		}
		break;

	case FIN:
		SetPIN(COIL0_0,LOW);
		SetPIN(COIL0_1,LOW);
		SetPIN(COIL0_2,LOW);
		SetPIN(COIL0_3,LOW);
		flag_stepper=-1;
		estado=next_estado;
		break;
	}
}

void M1_ClockWise_FullStep(void){

	static uint8_t estado=0,next_estado=0;

	switch (estado){
	case A:
		SetPIN(COIL1_3,LOW);
		SetPIN(COIL1_0,HIGH);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		estado=B;
		pasos_M1--;
		if ((pasos_M1)==1){
			estado=FIN;
			next_estado=B;
		}
		break;
	case B:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,HIGH);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,LOW);
		estado=C;
		pasos_M1--;
		if ((pasos_M1)==1){
			estado=FIN;
			next_estado=C;
		}
		break;
	case C:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,HIGH);
		SetPIN(COIL1_3,LOW);
		estado=D;
		pasos_M1--;
		if ((pasos_M1)==1){
			estado=FIN;
			next_estado=D;
		}
		break;
	case D:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,HIGH);
		estado = A;
		pasos_M1--;
		if ((pasos_M1)==1){
			estado=FIN;
			next_estado=A;
		}
		break;

	case FIN:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,LOW);
		flag_stepper=-1;
		estado=next_estado;
		break;
	}
}

void M1_Counter_ClockWise_FullStep(void){

	static uint8_t estado=0,next_estado=0;

	switch (estado){
	case A:
		SetPIN(COIL1_0,HIGH);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,LOW);
		estado=B;
		pasos_M1++;
		if ((pasos_M1)==-1){
			estado=FIN;
			next_estado=B;
		}
		break;

	case B:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,HIGH);
		estado=C;
		pasos_M1++;
		if ((pasos_M1)==-1){
			estado=FIN;
			next_estado=C;
		}
		break;

	case C:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,HIGH);
		SetPIN(COIL1_3,LOW);
		estado=D;
		pasos_M1++;
		if ((pasos_M1)==-1){
			estado=FIN;
			next_estado=D;
		}
		break;

	case D:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,HIGH);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,LOW);
		pasos_M1++;
		estado=A;
		if ((pasos_M1)==-1){
			estado=FIN;
			next_estado=A;
		}
		break;

	case FIN:
		SetPIN(COIL1_0,LOW);
		SetPIN(COIL1_1,LOW);
		SetPIN(COIL1_2,LOW);
		SetPIN(COIL1_3,LOW);
		flag_stepper=-1;
		estado=next_estado;
		break;
	}
}
