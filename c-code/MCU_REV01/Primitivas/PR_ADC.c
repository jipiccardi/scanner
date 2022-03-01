/*
 * PR_ADC.c
 *
 *  Created on: 10 dic. 2021
 *      Author: adrie
 */

#include "PR_ADC.h"



uint16_t LecturaADC(void){
	uint16_t r=-1;
	if(out_adc!=in_adc){
		r=Buffer_adc[out_adc];
		out_adc++;
		out_adc%=MAX_ADC;
	}return r;
}

void Enb_ADC (uint16_t k){
	flag_ADC=k;
	flag_TX=k;
	ADC->INTEN = 1;
}
