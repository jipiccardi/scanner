/*
 * DR_SysTick.h
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_

#include "LPC845.h"

#define MAX_T 5

extern uint32_t timer[MAX_T];
extern uint8_t flag_timer[MAX_T];


void Init_Systick (void);
void SysTick_Handler(void);

#endif /* DR_SYSTICK_H_ */
