/*
 * time_manip.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "time_manip.h"

unsigned char timeBuffer[TIME_DIGITS] = {};

void Time_Input (unsigned char hour, unsigned char minute){
	if (hour < 0 || hour >= HOUR_LIMIT
			|| minute < 0 || minute >= MINUTE_LIMIT) return;
	timeBuffer[0] = hour 	/ DEC_SEPARTION;
	timeBuffer[1] = hour 	% DEC_SEPARTION;
	timeBuffer[2] = minute 	/ DEC_SEPARTION;
	timeBuffer[3] = minute 	% DEC_SEPARTION;
}

