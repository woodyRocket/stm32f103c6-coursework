/*
 * mode.c
 *
 *  Created on: Nov 13, 2022
 *      Author: ttrng
 */

#include "mode.h"

MODE_STATE trafficMode = NORMAL;

void ModeButton_Pressed(void){
	if (buttonMode->flag == 1){
		buttonMode->flag = 0;
		trafficMode = (trafficMode + 1) % NO_OF_MODE;
	}
}

static uint16_t newRedTime 		= 0;
static uint16_t newYellowTime 	= 0;
static uint16_t newGreenTime 	= 0;

void Delay_Flush(void){
	newRedTime 		= 0;
	newYellowTime 	= 0;
	newGreenTime 	= 0;
}

uint16_t LightTime_Modify(uint16_t* newDelay){
	if (buttonTime->flag == 1){
		buttonTime->flag = 0;
		*newDelay = (*newDelay + 1) % UPPERBOUND;
	}
	return *newDelay;
}

void Mode_Processing(void){
	ModeButton_Pressed();
	switch(trafficMode){
		case NORMAL:
			if (standardTime->flag == 1){
				  standardTime->Set_Default(standardTime);
				  vClock->Down(vClock);
				  hClock->Down(hClock);
			}
			Intersection_Normal_Mode();
			break;
		case RED_MOD:
			if (stim2->flag == 1){
				stim2->Set_Default(stim2);
				vTrafficLight->Toggle_Red(vTrafficLight);
				hTrafficLight->Toggle_Red(hTrafficLight);
			}

			hClock->Modify(hClock, 0, 0, RED_MOD);
			vClock->Modify(vClock, 0, 0, LightTime_Modify(&newRedTime));
			if (stim3->flag == 1){
				stim3->Set_Default(stim3);
				Intersection_7SEG_Display();
			}
			if (buttonSet->flag == 1){
				buttonSet->flag = 0;
				H_RED_TIME = newRedTime*1000;
			}
			break;
		case YELLOW_MOD:
			if (stim2->flag == 1){
				stim2->Set_Default(stim2);
				vTrafficLight->Toggle_Yellow(vTrafficLight);
				hTrafficLight->Toggle_Yellow(hTrafficLight);
			}

			hClock->Modify(hClock, 0, 0, YELLOW_MOD);
			vClock->Modify(vClock, 0, 0, LightTime_Modify(&newYellowTime));
			if (stim3->flag == 1){
				stim3->Set_Default(stim3);
				Intersection_7SEG_Display();
			}
			if (buttonSet->flag == 1){
				buttonSet->flag = 0;
				H_YELLOW_TIME = newYellowTime*1000;
			}
			break;
		case GREEN_MOD:
			if (stim2->flag == 1){
				stim2->Set_Default(stim2);
				vTrafficLight->Toggle_Green(vTrafficLight);
				hTrafficLight->Toggle_Green(hTrafficLight);
			}

			hClock->Modify(hClock, 0, 0, GREEN_MOD);
			vClock->Modify(vClock, 0, 0, LightTime_Modify(&newGreenTime));
			if (stim3->flag == 1){
				stim3->Set_Default(stim3);
				Intersection_7SEG_Display();
			}
			if (buttonSet->flag == 1){
				buttonSet->flag = 0;
				H_GREEN_TIME = newGreenTime*1000;
			}
			break;
		case EXIT_MOD:
			Delay_Flush();
			Sub_Road(H_RED_TIME, H_YELLOW_TIME, H_GREEN_TIME);
			Main_Road(V_RED_TIME, V_YELLOW_TIME, V_GREEN_TIME);

			hTrafficLight->stim->Set_Manual(hTrafficLight->stim, H_YELLOW_TIME);
			vTrafficLight->stim->Set_Manual(vTrafficLight->stim, V_YELLOW_TIME);

			hTrafficLight->state = INIT;
			vTrafficLight->state = EXIT;

			vClock->Modify(vClock, 0, 0, V_GREEN_TIME/1000);
			hClock->Modify(hClock, 0, 0, H_RED_TIME/1000);

			trafficMode = NORMAL;
			break;
		default:
			break;
	}
}

void Set_Processing(void){
	if (buttonSet->flag == 1){
		buttonSet->flag = 0;

		H_RED_TIME = newRedTime;
		Sub_Road(H_RED_TIME, H_YELLOW_TIME, H_GREEN_TIME);

		vClock->Modify(vClock, 0, 0, V_GREEN_TIME/1000);
		hClock->Modify(hClock, 0, 0, H_RED_TIME/1000);
	}
}


