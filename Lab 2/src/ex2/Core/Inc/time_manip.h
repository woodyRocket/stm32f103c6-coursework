/*
 * time_manip.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_TIME_MANIP_H_
#define INC_TIME_MANIP_H_


#define TIME_DIGITS					4
#define HOUR_LIMIT 					24
#define MINUTE_LIMIT				60
#define SECOND_LIMIT				60
#define DEC_SEPARTION				10

typedef struct Clock_TypeDef{
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}Clock_Status;

extern unsigned char timeBuffer[];

void Time_Input(unsigned char hour, unsigned char minute, unsigned char second);

#endif /* INC_TIME_MANIP_H_ */
