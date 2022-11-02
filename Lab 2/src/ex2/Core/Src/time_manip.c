/*
 * time_manip.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "time_manip.h"

unsigned char timeBuffer[TIME_DIGITS] = {};
static Clock_Status clock;

void Time_Input (unsigned char hour, unsigned char minute, unsigned char second){
	if (hour < 0 || hour >= HOUR_LIMIT
			|| minute < 0 || minute >= MINUTE_LIMIT) return;

	clock.hour		= hour;
	clock.minute 	= minute;
	clock.second 	= second;

	timeBuffer[0] 	= clock.hour 		/ DEC_SEPARTION;
	timeBuffer[1] 	= clock.hour 		% DEC_SEPARTION;
	timeBuffer[2] 	= clock.minute 		/ DEC_SEPARTION;
	timeBuffer[3] 	= clock.minute 		% DEC_SEPARTION;
}

void Clock_Counter(void){
	clock.second++;
	if (clock.second >= SECOND_LIMIT){
		clock.second	= 0;
		clock.minute++;
	}
	if (clock.minute >= MINUTE_LIMIT){
		clock.minute 	= 0;
		clock.hour++;
	}
	if (clock.hour >= HOUR_LIMIT){
		clock.hour		= 0;
	}
}
