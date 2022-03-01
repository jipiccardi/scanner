/*
 * PR_SysTick.h
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#ifndef PR_SYSTICK_H_
#define PR_SYSTICK_H_

#include "..\Drivers\DR_SysTick.h"

#define MILI 1
#define SEC 1000
#define MIN 60000
#define M_TIMER 0



extern void (*handler_timer[MAX_T])(void);
extern int32_t flag_cron;
extern uint8_t flag_T_Wait,flag_M_fin;

void TimerStart(uint8_t ntimer,uint32_t time, void (*handler) (void), uint16_t base);
void TimerStop(uint8_t );
void TimerEvent(void);

void M_Timer_Handler(void);
void T1_Handler(void);
void T_Wait_Handler(void);

#endif /* PR_SYSTICK_H_ */
