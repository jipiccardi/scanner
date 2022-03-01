/*
 * DR_ADC.c
 *
 *  Created on: 10 dic. 2021
 *      Author: adrie
 */

#include "DR_ADC.h"


uint8_t in_adc=0;
uint8_t out_adc=0;
uint16_t Buffer_adc[MAX_ADC];
uint16_t flag_ADC=0;

void InitADC(void){
	SYSCON->PDRUNCFG &= ~(1<<4);
	SYSCON->SYSAHBCLKCTRL0 |= 1<<24;
	SYSCON->ADCCLKSEL = 0;
	SYSCON->ADCCLKDIV=1;

	SYSCON->SYSAHBCLKCTRL0 |= 1<<7;
	PINENABLE0 &= ~(1<<15);

	//Calibracion
	ADC->CTRL = (60 | 1<<30); // 30M/60 -> Frecuencdia de trabajo 500khz
	while (ADC->CTRL & 1<<30);

	//Seteo
	/*Cada pulso del sensor dura 38ms
	 * Max Div = 255 + 1
	 * Fs = 30M/(256*25) = 4687 Hz
	 * con Fs= 4687 tomo 178 muestras por pulso
	 */
	ADC->CTRL = (255) 	| // Freq de muestreo
				(0<<8) 	|
				(0<<10) |
				(0<<30) ;

	//Deshabilito la secuencia B:
		ADC->SEQB_CTRL = 0;

		//Selecciono VDD por encima de 2,7V (la alimentacion del ADC):
		ADC->TRM &= ~(1<<5);

	ADC->SEQA_CTRL = (1)<<1 | //CANAL 1
					0<<12	|
					0<<19	| //BYPASS OFF NO APARECE EN MANUAL DE CATEDRA
					0<<24	| //TSAMP OFF NO APARECE EN EL MANUAL DE CATEDRA
					1<<27	|
					0<<30	|
					1<<31;

	ADC->INTEN = 0;
	ISER0 |= 1<<16;
}


void ADC_SEQA_IRQHandler(void){
	Buffer_adc[in_adc]= (ADC->SEQA_GDAT>>4 & 0x0FFF);
	in_adc++;
	if(in_adc==100){
		in_adc=100;
	}
	in_adc%=MAX_ADC;
	flag_ADC--;
	if(flag_ADC==0)
		ADC->INTEN = 0;

}
