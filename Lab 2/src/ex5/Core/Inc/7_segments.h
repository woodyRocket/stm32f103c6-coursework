/*
 * 7_segments.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_7_SEGMENTS_H_
#define INC_7_SEGMENTS_H_

#include "main.h"
#include "enable_pin.h"
#include "time_manip.h"

#define NO_OF_SEGMENT 				7
#define NO_OF_7SEG_DEVICE			4


void Display_7SEG_Buffer(void);
void Number_Conversion(unsigned char number);
void Segment_Processing(void);
#endif /* INC_7_SEGMENTS_H_ */
