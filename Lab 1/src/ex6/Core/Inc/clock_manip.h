/*
 * clock_display.h
 *
 *  Created on: Oct 29, 2022
 *      Author: ttrng
 */

#ifndef INC_CLOCK_MANIP_H_
#define INC_CLOCK_MANIP_H_

#include <stdint.h>

#define 	HOUR_LIMIT 			12
#define 	MINUTE_LIMIT		60
#define		SECOND_LIMIT		60
#define 	CLOCK_LOD			5

void Check_Clock(void);
void Clear_All(void);
void Set_Number(uint8_t number);
void Clear_Number(uint8_t number);
void Display_Time(uint8_t hour, uint8_t minute, uint8_t second);


#endif /* INC_CLOCK_MANIP_H_ */
