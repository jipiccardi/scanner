#ifndef DR_GPIO_H_
#define DR_GPIO_H_

#include "LPC845.h"

#define LOW		0
#define HIGH	1


#define PIN_LEDR	1,2

#define	PIN_LEDG	1,0
#define	PIN_LEDB	1,1
/*
#define PIN_LED0	1,0
#define PIN_LED1	1,1
#define PIN_LED2	1,2
#define PIN_LED3	0,1
*/

void SetDIR (uint32_t Puerto, uint32_t Pin, uint32_t Direccion);	//Setea la dirección del pin especificado
void SetPIN (uint32_t Puerto, uint32_t Pin, uint32_t Estado);	//Setea el Estado (0 o 1) indicado en el pin especificado
uint32_t GetPIN (uint32_t Puerto, uint32_t Pin); //Devuelve el valor del pin especificado
void SetPINMODE_IN (uint32_t Pin_index, uint32_t Modo); 	//Pull-Down o Pull-Up
void SetPINMODE_OUT (uint32_t Pin_index, uint32_t Modo);	//Drain Mode
void InitGPIO(void);

#endif /* DR_GPIO_H_ */
