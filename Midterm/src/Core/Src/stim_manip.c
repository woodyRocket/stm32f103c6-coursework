/*
 * stim_manip.c
 *
 *  Created on: Nov 3, 2022
 *      Author: ttrng
 */

#include "stim_manip.h"

STIM_TypeDef* stim2;
STIM_TypeDef* rst_stim;
STIM_TypeDef* inc_stim;
STIM_TypeDef* dec_stim;
STIM_TypeDef* subBstim3;
STIM_TypeDef* standardTime;

void Software_Timer_Init(void){
	stim2 				= STIM_Init(STIM2_TIMER_DELAY, TIM2_TIMER_INTERRUPT);
	rst_stim 			= STIM_Init(BUTTON_TIMER_HOLD, TIM2_TIMER_INTERRUPT);
	inc_stim 			= STIM_Init(BUTTON_TIMER_HOLD, TIM2_TIMER_INTERRUPT);
	dec_stim 			= STIM_Init(BUTTON_TIMER_HOLD, TIM2_TIMER_INTERRUPT);
	subBstim3			= STIM_Init(SUB_BUTTON_TIMER, TIM2_TIMER_INTERRUPT);
	standardTime 		= STIM_Init(STANDARD_TIME_DELAY, TIM2_TIMER_INTERRUPT);

	stim2->Set_Default(stim2);
//	rst_stim->Set_Default(rst_stim);
//	inc_stim->Set_Default(inc_stim);
//	dec_stim->Set_Default(dec_stim);
	subBstim3->Set_Default(subBstim3);
	standardTime->Set_Default(standardTime);
}

void Software_Timer_Run(void){
	stim2->Timer_Run(stim2);
	standardTime->Timer_Run(standardTime);
}
