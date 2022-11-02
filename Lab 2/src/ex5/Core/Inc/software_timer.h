/*
 * software_timer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_SOFTWARE_TIMER_C_
#define INC_SOFTWARE_TIMER_C_

/*
 * SOFTWARE_TIMER
 * Using struct to characterize the properties of the software timer including delay, interrupt, counter, flag
 * and function pointer to setup and counting
 * In this lab, I use 2 hardware timers TIM2 and TIM3
 * TIM2 controls 2 software timers standardTime and stim2
 * standardTime is running on TIM2 and fixed to count time on clock, delay is 1s
 * TIM3 controls 1 software timers stim3
 * Indeed, it may save resources if use only 1 hardware timer and create 3 software timers.
 */

#define STANDARD_TIME_DELAY				1000

#define STIM2_TIMER_DELAY				200
#define STIM3_TIMER_DELAY				500
#define TIM2_TIMER_INTERRUPT 			10
#define TIM3_TIMER_INTERRUPT 			20


typedef struct Software_TIM{
	int delay;
	int interrupt;
	int counter;
	unsigned char flag;

	void (*Set_Timer)(struct Software_TIM* tim);
	void (*Timer_Run)(struct Software_TIM* tim);
}STIM_TypeDef;

extern STIM_TypeDef stim2;

extern STIM_TypeDef stim3;

extern STIM_TypeDef standardTime;

void Software_Timer_Init(void);
void STIM_Set_Timer(STIM_TypeDef* tim);
void STIM_Timer_Run(STIM_TypeDef* tim);


#endif /* INC_SOFTWARE_TIMER_C_ */
