/*
 * software_timer.c
 *
 *  Created on: Oct 7, 2022
 *      Author: ttrng
 */

#include "software_timer.h"

int timerCounter = 0;
int timerFlag = 0;

void Set_Timer(void){
	timerCounter = TIMER_DELAY/TIMER_INTERRUPT;
	timerFlag 	 = 0;
}

void Timer_Run(void){
	if(timerCounter > 0){
		timerCounter--;
		if(timerCounter <= 0){
			timerFlag = 1;
		}
	}
}
