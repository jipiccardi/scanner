/*
 * PR_Stepper.h
 *
 *  Created on: 5 dic. 2021
 *      Author: adrie
 */

#ifndef PR_STEPPER_H_
#define PR_STEPPER_H_

#include "..\Drivers\DR_Stepper.h"

#define PPS 30
#define PPS_M0 10

void Motor0_UP(int32_t );
void Motor0_DOWN(int32_t );

void Motor1_Clockwise(uint32_t );
void Motor1_CounterClockwise(uint32_t );

void MotorControl(void);

#endif /* PR_STEPPER_H_ */
