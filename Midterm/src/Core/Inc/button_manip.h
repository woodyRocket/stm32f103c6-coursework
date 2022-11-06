/*
 * button_manip.h
 *
 *  Created on: Nov 6, 2022
 *      Author: ttrng
 */

#ifndef INC_BUTTON_MANIP_H_
#define INC_BUTTON_MANIP_H_

#include "component.h"
#include "stim_manip.h"

#define NO_OF_BUTTON			3

typedef enum FSM_State{
	START,
	REST,
	INCRE,
	DECRE,
	IDLE
}FSM_Type;

extern Button_TypeDef* reset;
extern Button_TypeDef* increase;
extern Button_TypeDef* decrease;
extern int8_t currentValue;

void FSM_Button_Init(void);
void FSM_Button_Read(void);
void FSM_Simple_Run(void);
void Count_Down(int8_t number);


#endif /* INC_BUTTON_MANIP_H_ */
