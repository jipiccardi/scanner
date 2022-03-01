/*
 * DR_ADC.h
 *
 *  Created on: 10 dic. 2021
 *      Author: adrie
 */

#ifndef DR_ADC_H_
#define DR_ADC_H_

#include "LPC845.h"

#define MAX_ADC 200

extern uint8_t in_adc;
extern uint8_t out_adc;
extern uint16_t Buffer_adc[MAX_ADC];
extern uint16_t flag_ADC;

void InitADC(void);
void ADC_SEQA_IRQHandler(void);

#endif /* DR_ADC_H_ */
