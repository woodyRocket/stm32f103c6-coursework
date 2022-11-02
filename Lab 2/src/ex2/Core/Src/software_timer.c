/*
 * software_timer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#include "software_timer.h"

unsigned char timerCounter = 0;
unsigned char timerFlag = 0;

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

