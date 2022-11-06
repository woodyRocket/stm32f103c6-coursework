/*
 * 7_segments.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_7SEG_MANIP_H_
#define INC_7SEG_MANIP_H_

#include "component.h"
#include "button_manip.h"

#define NO_OF_7SEG_DEVICE			1

void SevenSEG_Init(void);
void Update_State(void);
void State_To_Buffer(void);
void SevenSEG_Display(void);

#endif /* INC_7SEG_MANIP_H_ */
