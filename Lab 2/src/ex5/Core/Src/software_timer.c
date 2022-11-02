/*
 * software_timer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#include "software_timer.h"

STIM_TypeDef stim2;

STIM_TypeDef stim3;

STIM_TypeDef standardTime;

void Software_Timer_Init(void){
	stim2.delay  				= STIM2_TIMER_DELAY;
	stim2.interrupt 			= TIM2_TIMER_INTERRUPT;
	stim2.Set_Timer 			= STIM_Set_Timer;
	stim2.Timer_Run				= STIM_Timer_Run;

	stim3.delay  				= STIM3_TIMER_DELAY;
	stim3.interrupt 			= TIM3_TIMER_INTERRUPT;
	stim3.Set_Timer 			= STIM_Set_Timer;
	stim3.Timer_Run				= STIM_Timer_Run;

	standardTime.delay  		= STANDARD_TIME_DELAY;
	standardTime.interrupt 		= TIM2_TIMER_INTERRUPT;
	standardTime.Set_Timer 		= STIM_Set_Timer;
	standardTime.Timer_Run		= STIM_Timer_Run;


	stim2.Set_Timer(&stim2);
	stim3.Set_Timer(&stim3);
	standardTime.Set_Timer(&standardTime);
}

void STIM_Set_Timer(STIM_TypeDef* stim){
	stim->counter 			= stim->delay/stim->interrupt;
	stim->flag 	 			= 0;
}

void STIM_Timer_Run(STIM_TypeDef* stim){
	if(stim->counter > 0){
		stim->counter--;
		if(stim->counter <= 0){
			stim->flag = 1;
		}
	}
}

