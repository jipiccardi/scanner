/*
 * Main.h
 *
 *  Created on: 30 ene. 2022
 *      Author: adrie
 */

#ifndef MAIN_H_
#define MAIN_H_


#include "Mde_Fwd_Bck.h"
#include "Mde_Manual.h"
#include "Mde_Scan.h"
#include "Mde_Serial.h"
#include "Mde_General.h"
#include "..\Drivers\DR_Init.h"

#define FALSE 0
#define TRUE 1

#define SCAN 1
#define STOP 2
#define PAUSE 3
#define CAL 4
#define MANUAL 5
#define NO_MODE 6
#define FOWARD 7
#define BACK 8



void Stop_All();
#endif /* MAIN_H_ */
