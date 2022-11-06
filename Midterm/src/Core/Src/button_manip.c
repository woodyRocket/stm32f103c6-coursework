/*
 * button_manip.c
 *
 *  Created on: Nov 6, 2022
 *      Author: ttrng
 */

#include "button_manip.h"

static uint16_t buttonPin[NO_OF_BUTTON] = {
		RST_Pin,
		INC_Pin,
		DEC_Pin
};

static GPIO_TypeDef * buttonPort[NO_OF_BUTTON] = {
		RST_GPIO_Port,
		INC_GPIO_Port,
		DEC_GPIO_Port
};


Button_TypeDef* reset;
Button_TypeDef* increase;
Button_TypeDef* decrease;

FSM_Type fsm_status = START;
int8_t currentValue = 5;


void FSM_Button_Init(void){
	reset 		= Button_Init(buttonPort[0], buttonPin[0], rst_stim);
	increase 	= Button_Init(buttonPort[1], buttonPin[1], inc_stim);
	decrease 	= Button_Init(buttonPort[2], buttonPin[2], dec_stim);
}

void FSM_Button_Read(void){
//	reset->Read(reset);
//	increase->Read(increase);
	decrease->Read(decrease);
}

void Reset_Button(void){
	if (reset->state != FREE)
		currentValue = 0;
}

void Incre_Button(void){
	switch(increase->state){
		case TAP:
			currentValue = (currentValue + 1) % DECIMAL;
			break;
		case HOLD:
			currentValue = (currentValue + 1) % DECIMAL;
			break;
		default:
			break;
	}
}

void Decre_Button(void){
	switch(decrease->state){
		case TAP:
			Count_Down(currentValue);
			break;
		case HOLD:
			Count_Down(currentValue);
			break;
		default:
			break;
	}
}
FSM_Type FSM_Identifier(void){
	if (reset->state != FREE) return REST;
	else if (increase->state != FREE) return INCRE;
	else if (decrease->state != FREE) return DECRE;
	return IDLE;
}

void FSM_Simple_Run(void){
	//Reset_Button();
	//Incre_Button();
	Decre_Button();
}
void Count_Down(int8_t number){
	if (number < 0)
		number = 9;
	while (number >= 0){
		number--;
	}
}

