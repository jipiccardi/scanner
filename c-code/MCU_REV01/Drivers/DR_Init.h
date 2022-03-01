#ifndef DR_INIT_H_
#define DR_INIT_H_

//Registros de control del FRO y del CLK

//Direccion de la funcion de ROM para setear la frecuencia del oscilador:
#define FRO_SET_FRECUENCY_FUNC ( 0x0F0026F5U)

#include "DR_SysTick.h"
#include "DR_GPIO.h"
#include "DR_Stepper.h"
#include "DR_ADC.h"
#include "DR_UART.h"

void InitHw(void);
void InitPLL(void);

#endif /* DR_INIT_H_ */
