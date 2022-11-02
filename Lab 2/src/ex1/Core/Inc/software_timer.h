/*
 * software_timer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_SOFTWARE_TIMER_C_
#define INC_SOFTWARE_TIMER_C_

#define TIMER_DELAY			200
#define TIMER_INTERRUPT 	10

extern unsigned char timerFlag;

void Set_Timer(void);
void Timer_Run(void);

#endif /* INC_SOFTWARE_TIMER_C_ */
