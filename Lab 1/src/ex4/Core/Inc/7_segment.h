/*
 * 7_segment.h
 *
 *  Created on: Oct 27, 2022
 *      Author: ttrng
 */

#ifndef INC_7_SEGMENT_H_
#define INC_7_SEGMENT_H_

#include <stdint.h>

#define NUMBER_OF_SEGMENT			7
#define DECIMAL_COUNTER				10

void Display_Number(uint8_t data);
void Seg_Setup(uint8_t counter);
void Display_7Seg(void);

#endif /* INC_7_SEGMENT_H_ */
