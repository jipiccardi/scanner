/*
 * SysTick.c
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#include "DR_SysTick.h"

uint32_t timer[MAX_T];
uint8_t flag_timer[MAX_T];


void Init_Systick (void){
	SYSTICK->CSR =	7;
	SYSTICK->RVR = 30000-1; //30M / 1000
	SYSTICK->CVR = SYSTICK->RVR;


}

void SysTick_Handler(void){
	uint8_t aux = SYSTICK->CSR;
	for (uint8_t i=0; i<MAX_T; i++){
		if(timer[i]!=0){
			timer[i]--;
			if (timer[i]==0)
				flag_timer[i]=1;
		}
	}
}
