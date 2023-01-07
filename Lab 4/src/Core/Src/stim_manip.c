/*
 * stim_manip.c
 *
 *  Created on: Nov 3, 2022
 *      Author: ttrng
 */

#include "stim_manip.h"

STIM_TypeDef* standardTime;

void Software_Timer_Init(void){
	standardTime 	= STIM_Init(STANDARD_TIME_DELAY, TIM2_TIMER_INTERRUPT);

	standardTime->Set_Default(standardTime);
}

void Software_Timer_Run(void){
	standardTime->Timer_Run(standardTime);
}
