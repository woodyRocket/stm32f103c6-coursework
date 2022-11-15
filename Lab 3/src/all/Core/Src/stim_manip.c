/*
 * stim_manip.c
 *
 *  Created on: Nov 3, 2022
 *      Author: ttrng
 */

#include "stim_manip.h"

STIM_TypeDef* stim2;
STIM_TypeDef* stim3;
STIM_TypeDef* standardTime;

void Software_Timer_Init(void){
	stim2 			= STIM_Init(STIM2_TIMER_DELAY, TIM2_TIMER_INTERRUPT);
	stim3 			= STIM_Init(STIM3_TIMER_DELAY, TIM2_TIMER_INTERRUPT);
	standardTime 	= STIM_Init(STANDARD_TIME_DELAY, TIM2_TIMER_INTERRUPT);

	stim2->Set_Default(stim2);
	stim3->Set_Default(stim3);
	standardTime->Set_Default(standardTime);
}

void Software_Timer_Run(void){
	stim2->Timer_Run(stim2);
	stim3->Timer_Run(stim3);
	standardTime->Timer_Run(standardTime);
}
