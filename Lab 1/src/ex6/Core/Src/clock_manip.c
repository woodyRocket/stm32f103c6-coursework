/*
 * clock_display.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ttrng
 */


#include <clock_manip.h>
#include "gpio.h"


static uint8_t clockBuffer[ANALOG_CLOCK_NUMBER] =
{
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE
};

void Check_Clock(void){
	static uint8_t index 	= 0;
	clockBuffer[index] 		= ENABLE;
	for (uint8_t tempIndex = 0; tempIndex < ANALOG_CLOCK_NUMBER; tempIndex++){
		if (tempIndex != index)
			clockBuffer[tempIndex] = DISABLE;
	}
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
	index = (index + 1) % ANALOG_CLOCK_NUMBER;
}
void Clear_All(void){
	for (uint8_t tempIndex = 0; tempIndex < ANALOG_CLOCK_NUMBER; tempIndex++){
		clockBuffer[tempIndex] = DISABLE;
	}
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
}
void Set_All(void){
	for (uint8_t tempIndex = 0; tempIndex < ANALOG_CLOCK_NUMBER; tempIndex++){
		clockBuffer[tempIndex] = ENABLE;
	}
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
}
void Set_Number(uint8_t number){
	Clear_All();
	if (number < 0 || number >= ANALOG_CLOCK_NUMBER) return;
	clockBuffer[number] = ENABLE;
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
}
void Clear_Number(uint8_t number){
	if (number < 0 || number >= ANALOG_CLOCK_NUMBER) return;
	clockBuffer[number] = DISABLE;
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
}
void Display_Time(uint8_t hour, uint8_t minute, uint8_t second){
	if 	(hour < 0 || hour >= 2*HOUR_LIMIT
			|| minute < 0 || minute >= MINUTE_LIMIT
			|| second < 0 || second >= SECOND_LIMIT) return;
	clockBuffer[hour % HOUR_LIMIT]  	= ENABLE;
	clockBuffer[minute / CLOCK_LOD] 	= ENABLE;
	clockBuffer[second / CLOCK_LOD] 	= ENABLE;
	Clock_Display(clockBuffer, ANALOG_CLOCK_NUMBER);
}
