/*
 * stim_manip.h
 *
 *  Created on: Nov 3, 2022
 *      Author: ttrng
 */

#ifndef INC_STIM_MANIP_H_
#define INC_STIM_MANIP_H_

#include "component.h"

#define STANDARD_TIME_DELAY				1000
#define TIM2_TIMER_INTERRUPT 			10

extern STIM_TypeDef* standardTime;

void Software_Timer_Init(void);
void Software_Timer_Run(void);
#endif /* INC_STIM_MANIP_H_ */
