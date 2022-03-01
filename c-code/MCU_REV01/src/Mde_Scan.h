/*
 * Mde_Scan.h
 *
 *  Created on: 10 dic. 2021
 *      Author: adrie
 */

#ifndef MDE_SCAN_H_
#define MDE_SCAN_H_

#include "..\Primitivas\PR_ADC.h"
#include "..\Primitivas\PR_Stepper.h"
#include "..\Primitivas\PR_SysTick.h"
#include "..\Primitivas\PR_UART.h"

#define HEIGHT 900 // 8cm

/*
 * 178 muestras por pulso
 * Se miden 3 pulsos del sensor
 * En total se obtienen 534 muestras por punto
 */
#define MEDxP 200

#define INICIO 		0
#define WAIT_PARAMETER_A 1
#define WAIT_PARAMETER_B 2
#define MED			3
#define ROT			4
#define Z_MOVE		5
#define FIN_SCAN	6

extern uint16_t flag_rot;
extern uint16_t flag_height;
extern int8_t flag_mode;

void Mde_Scan();


#endif /* MDE_SCAN_H_ */
