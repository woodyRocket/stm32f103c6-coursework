/*
 * button_manip.c
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */


#include "button_manip.h"

static uint16_t buttonPin[NO_OF_BUTTON] = {
		MODE_Pin,
		TIME_Pin,
		SET_Pin
};

static GPIO_TypeDef * buttonPort[NO_OF_BUTTON] = {
		MODE_GPIO_Port,
		TIME_GPIO_Port,
		SET_GPIO_Port
};

Button_TypeDef* buttonMode;
Button_TypeDef* buttonTime;
Button_TypeDef* buttonSet;

void Traffic_Button_Init(void){
	buttonMode	= Button_Init(buttonPort[0], buttonPin[0], NULL);
	buttonTime	= Button_Init(buttonPort[1], buttonPin[1], NULL);
	buttonSet	= Button_Init(buttonPort[2], buttonPin[2], NULL);
}

void Button_Scan(void){
	buttonMode->Tap_Mode(buttonMode);
	buttonTime->Tap_Mode(buttonTime);
	buttonSet->Tap_Mode(buttonSet);
}


