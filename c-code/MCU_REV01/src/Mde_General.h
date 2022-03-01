/*
 * Mde_General.h
 *
 *  Created on: 9 feb. 2022
 *      Author: adrie
 */

#ifndef MDE_GENERAL_H_
#define MDE_GENERAL_H_

#include "Mde_General.h"
#include "Main.h"

#define SCAN 1
#define CAL 4
#define MANUAL 5
#define NO_MODE 6
#define FOWARD 7
#define BACK 8

extern int8_t flag_fin;
extern uint8_t flag_stop;

void Mde_General();

void Stop_All();
void Led_Off();
void Led_On();

#endif /* MDE_GENERAL_H_ */
