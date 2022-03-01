/*
 * PR_SysTick.c
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#include "PR_SysTick.h"

void ( * handler_timer[MAX_T]) (void);
int32_t flag_cron=0;
uint8_t flag_T_Wait=0,flag_M_fin=0;

void TimerStart(uint8_t ntimer,uint32_t time, void (*handler) (void), uint16_t base){
	timer[ntimer]=time*base;
	handler_timer[ntimer]=handler;
	flag_timer[ntimer]=0;
}

void TimerStop(uint8_t ntimer){
	timer[ntimer]=0;
	flag_timer[ntimer]=0;
}

void TimerEvent(void){
	for (uint8_t i=0;i<MAX_T;i++){
		if (flag_timer[i]==1){
			flag_timer[i]=0;
			handler_timer[i]();
		}
	}
}

void M_Timer_Handler(void){
	MotorControl();
}
void T1_Handler(void){ //USADO PARA MEDIR TIEMPOS DE EJECUCION
	TimerStart(1,1,T1_Handler,MILI);
	flag_cron++;
}

void T_Wait_Handler(void){
	flag_T_Wait=1;
}
