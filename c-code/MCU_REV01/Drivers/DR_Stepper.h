/*
 * DR_Stepper.h
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#ifndef DR_STEPPER_H_
#define DR_STEPPER_H_

#include "LPC845.h"
#include "DR_GPIO.h"


#define A 0
#define B 1
#define C 2
#define D 3
#define FIN 4

#define COIL0_0		0,16
#define COIL0_1		0,17
#define COIL0_2		0,18
#define COIL0_3		0,19

#define COIL1_0		0,20
#define COIL1_1		0,21
#define COIL1_2		0,22
#define COIL1_3		0,23

extern int32_t pasos_M0;
extern int32_t pasos_M1;
extern uint8_t flag_stepper;

void InitStepper(void);

void M0_ClockWise_FullStep(void);
void M0_Counter_ClockWise_FullStep(void);

void M1_ClockWise_FullStep(void);
void M1_Counter_ClockWise_FullStep(void);

#endif /* DR_STEPPER_H_ */
