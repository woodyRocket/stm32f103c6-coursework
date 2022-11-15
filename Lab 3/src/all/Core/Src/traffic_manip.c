/*
 * traffic._light.c
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */

#include "traffic_manip.h"

uint16_t vPin[NO_OF_LIGHT] = {
	V_RED_Pin,
	V_YEL_Pin,
	V_GRE_Pin
};

uint16_t hPin[NO_OF_LIGHT] = {
	H_RED_Pin,
	H_YEL_Pin,
	H_GRE_Pin
};

GPIO_TypeDef * vPort[NO_OF_LIGHT] = {
	V_RED_GPIO_Port,
	V_YEL_GPIO_Port,
	V_GRE_GPIO_Port
};

GPIO_TypeDef * hPort[NO_OF_LIGHT] = {
	H_RED_GPIO_Port,
	H_YEL_GPIO_Port,
	H_GRE_GPIO_Port
};

Traffic_TypeDef * hTrafficLight = NULL;
Traffic_TypeDef * vTrafficLight = NULL;

Clock_TypeDef* vClock;
Clock_TypeDef* hClock;

uint16_t V_YELLOW_TIME;
uint16_t V_RED_TIME;
uint16_t V_GREEN_TIME;
uint16_t H_YELLOW_TIME;
uint16_t H_RED_TIME;
uint16_t H_GREEN_TIME;

void Sub_Road(uint16_t mainRed, uint16_t mainYellow, uint16_t mainGreen){
	V_YELLOW_TIME 	= 2000;
	V_GREEN_TIME 	= (mainRed) 	-	V_YELLOW_TIME;
	V_RED_TIME 		= (mainGreen)	+	(mainYellow);
}

void Main_Road(uint16_t subRed, uint16_t subYellow, uint16_t subGreen){
	H_YELLOW_TIME 	= 2000;
	H_GREEN_TIME 	= (subRed)		-	H_YELLOW_TIME;
	H_RED_TIME		= (subGreen) 	+	(subYellow);
}

void Intersection_Init(void){
	Sub_Road(H_RED_TIME_EX, H_YELLOW_TIME_EX, H_GREEN_TIME_EX);
	Main_Road(V_RED_TIME, V_YELLOW_TIME, V_GREEN_TIME);

	hTrafficLight = Traffic_Init(hPort, hPin, STIM_Init(H_YELLOW_TIME, TIM2_TIMER_INTERRUPT));
	vTrafficLight = Traffic_Init(vPort, vPin, STIM_Init(V_YELLOW_TIME, TIM2_TIMER_INTERRUPT));

	hTrafficLight->state = INIT;
	vTrafficLight->state = EXIT;

	vClock = Clock_Init(0, 0, V_GREEN_TIME/1000);
	hClock = Clock_Init(0, 0, H_RED_TIME/1000);
}


void Intersection_Normal_Mode(void){
	vTrafficLight->Normal_Run(vTrafficLight, vClock, V_RED_TIME, V_YELLOW_TIME, V_GREEN_TIME);
	hTrafficLight->Normal_Run(hTrafficLight, hClock, H_RED_TIME, H_YELLOW_TIME, H_GREEN_TIME);
}
