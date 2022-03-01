/*
 * Mde_General.c
 *
 *  Created on: 9 feb. 2022
 *      Author: adrie
 */
#include "Mde_General.h"

int8_t flag_fin=FALSE;
uint8_t flag_stop=FALSE;

void Mde_General(){
	static uint8_t state=6;

	switch (state){
		case SCAN:
			if (signal==CHAR_STOP || flag_fin==TRUE){
				flag_fin=FALSE;
				signal=0;
				Stop_All();
				state=NO_MODE;
			}else Mde_Scan();
			break;

		case MANUAL:
			if (signal==CHAR_STOP || flag_fin==TRUE){
				flag_fin=FALSE;
				signal=0;
				Stop_All();
				state=NO_MODE;
			}else Mde_Manual();
			break;

		case CAL:
			if (signal==CHAR_STOP || flag_fin==TRUE){
				flag_fin=FALSE;
				signal=0;
				Stop_All();
				state=NO_MODE;
			}else //Mde_Cal();
			break;

		case FOWARD:
			if (signal==CHAR_STOP){
				signal=0;
				Stop_All();
				state=NO_MODE;
			}else Mde_Fwd_Bck(FWD);
			break;

		case BACK:
			if (signal==CHAR_STOP){
				signal=0;
				Stop_All();
				state=NO_MODE;
			}else Mde_Fwd_Bck(BCK);
			break;

		case NO_MODE:
			if (!signal)
				state=NO_MODE;
			else if (signal==CHAR_SCAN){
				in_tx=0;
				out_tx=0;
				signal=0;
				Led_On();
				state=SCAN;
				Mde_Scan();
			}else if (signal==CHAR_CAL){
				signal=0;
				Led_On();
				state=CAL;
				//Mde_Cal();
			}else if (signal==CHAR_MAN){
				signal=0;
				Led_On();
				state=MANUAL;
				Mde_Manual();
			}else if (signal==CHAR_FWD){
				signal=0;
				Led_On();
				state=FOWARD;
				Mde_Fwd_Bck(FWD);
			}else if (signal==CHAR_BCK){
				signal=0;
				Led_On();
				state=FOWARD;
				Mde_Fwd_Bck(BCK);
			}break;

		default:
			state=NO_MODE;
			Stop_All();
		}
}

void Stop_All(){
	flag_stop=TRUE;
	pasos_M0=0;
	//Apago los motores
	SetPIN(COIL0_3,LOW);
	SetPIN(COIL0_0,LOW);
	SetPIN(COIL0_1,LOW);
	SetPIN(COIL0_2,LOW);
	pasos_M1=0;
	SetPIN(COIL1_3,LOW);
	SetPIN(COIL1_0,LOW);
	SetPIN(COIL1_1,LOW);
	SetPIN(COIL1_2,LOW);


	//Detengo los timers
	TimerStop(2);

	Led_Off();
}

void Led_Off(){
	SetPIN(PIN_LEDB,LOW);
	SetPIN(PIN_LEDG,HIGH);
}
void Led_On(){
	SetPIN(PIN_LEDB,HIGH);
	SetPIN(PIN_LEDG,LOW);
}

