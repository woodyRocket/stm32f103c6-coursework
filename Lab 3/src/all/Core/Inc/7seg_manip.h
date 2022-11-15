/*
 * 7_segments.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_7SEG_MANIP_H_
#define INC_7SEG_MANIP_H_

#include "component.h"
#include "traffic_manip.h"

#define NO_OF_7SEG_DEVICE			2

void Intersection_7SEG_Init(void);
void Segment_To_Buffer(void);
void Intersection_7SEG_Display(void);

#endif /* INC_7SEG_MANIP_H_ */
