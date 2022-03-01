/*
 * PR_Stepper.c
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */


#include "PR_Stepper.h"
#include "PR_SysTick.h"

/* Paso de varilla = 8mm
 * Pasos Motor = 2048
 * Minima ditancia en Z = 0,125mm
 * Minimo angulo de rotación = 0.703125°
 */

//X será cantidad de minima diviciones a avanzar o girar
void Motor0_UP(int32_t x){
	pasos_M0=x+1;
	flag_stepper=0;
	MotorControl();
}
void Motor0_DOWN(int32_t x){
	pasos_M0=x-1;
	flag_stepper=0;
	MotorControl();
}

void Motor1_Clockwise(uint32_t x){
	pasos_M1=x+1;
	flag_stepper=1;
	MotorControl();
}
void Motor1_CounterClockwise(uint32_t x){
	pasos_M1=-x-1;
	flag_stepper=1;
	MotorControl();
}

void MotorControl(void){
	if (flag_stepper==0){
		if(pasos_M0>0){
			M0_ClockWise_FullStep();
			TimerStart(M_TIMER,PPS_M0,M_Timer_Handler,MILI);
		}if(pasos_M0<0){
			M0_Counter_ClockWise_FullStep();
			TimerStart(M_TIMER,PPS_M0,M_Timer_Handler,MILI);
		}
	}if (flag_stepper==1){
		if(pasos_M1>0){
			M1_ClockWise_FullStep();
			TimerStart(M_TIMER,PPS,M_Timer_Handler,MILI);
		}if(pasos_M1<0){
			M1_Counter_ClockWise_FullStep();
			TimerStart(M_TIMER,PPS,M_Timer_Handler,MILI);
		}
	}
}
