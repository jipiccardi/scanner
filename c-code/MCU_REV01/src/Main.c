/*
===============================================================================
 Name        : TPO.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>
#include "Main.h"


// TODO: insert other include files here

// TODO: insert other definitions and declarations here


int main(void) {
	int16_t dato=-1;

	InitHw();
	SetPIN(PIN_LEDR,HIGH);
	SetPIN(PIN_LEDG,HIGH);
	SetPIN(PIN_LEDB,LOW);

	//TimerStart(1,1,T1_Handler,MILI); //Cronometro interno para ver tiempos de ejecucion etc
    while(1) {
    	dato=RecibirSerie();
    	if(dato!=-1)
    		Mde_Serial(dato);
    	Mde_General();
    	TimerEvent();

    }
    return 0 ;
}


