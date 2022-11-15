/*
 * component.c
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */


#include "component.h"

/**************************************************************************************/
/*
 * SOFTWARE TIMER TYPE DEFINITION
 */
/**************************************************************************************/

STIM_TypeDef * STIM_Init(uint16_t delay, uint16_t interrupt){
	STIM_TypeDef * stim 		= malloc(sizeof(STIM_TypeDef));
	stim->delay 				= delay;
	stim->interrupt 			= interrupt;
	stim->counter				= 0;

	stim->Set_Default 			= STIM_Set_Default;
	stim->Set_Manual			= STIM_Set_Manual;
	stim->Timer_Run 			= STIM_Timer_Run;
	return stim;
}
void STIM_Set_Default(STIM_TypeDef* stim){
	stim->counter 			= stim->delay/stim->interrupt;
	stim->flag 	 			= 0;
}
void STIM_Set_Manual(STIM_TypeDef* stim, uint16_t delay){
	stim->delay				= delay;
	stim->counter 			= stim->delay/stim->interrupt;
	stim->flag 	 			= 0;
}
void STIM_Timer_Run(STIM_TypeDef* stim){
	if(stim->counter > 0){
		stim->counter--;
		if(stim->counter <= 0){
			stim->flag = 1;
		}
	}
}

/**************************************************************************************/
/*
 * LED TYPE DEFINITION
 */
/**************************************************************************************/


LED_TypeDef * Led_Init(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state){
	LED_TypeDef * led 	= malloc(sizeof(LED_TypeDef));
	led->port 			= port;
	led->pin 			= pin;
	led->state 			= state;
	led->Display 		= Led_Display;
	led->On 			= Led_On;
	led->Off 			= Led_Off;
	led->Toggle 		= Led_Toggle;
	return led;
}

void Led_Display(LED_TypeDef* led){
	HAL_GPIO_WritePin(led->port, led->pin, led->state);
}
void Led_Toggle(LED_TypeDef* led){
	HAL_GPIO_TogglePin(led->port, led->pin);
}
void Led_On(LED_TypeDef* led){
	led->state = ENABLE;
	Led_Display(led);
}
void Led_Off(LED_TypeDef* led){
	led->state = DISABLE;
	Led_Display(led);
}


/**************************************************************************************/
/*
 * CLOCK TYPE DEFINTION
 */
/**************************************************************************************/

Clock_TypeDef * Clock_Init (uint8_t hour, uint8_t minute, uint8_t second){
	Clock_TypeDef * clock 	= malloc(sizeof(Clock_TypeDef));

	clock->hour				= hour;
	clock->minute 			= minute;
	clock->second 			= second;
	clock->Modify			= Time_Modify;
	clock->Up				= Clock_Counter_Up;
	clock->Down				= Clock_Counter_Down;
	clock->Update			= Update_Clock_Buffer;

	clock->Update(clock);
	return clock;
}
void Time_Modify(Clock_TypeDef* clock, uint8_t hour, uint8_t minute, uint8_t second){
	clock->hour 		= hour;
	clock->minute		= minute;
	clock->second 		= second;
	clock->Update(clock);
}

void Clock_Counter_Up(Clock_TypeDef* clock){
	clock->second++;
	if (clock->second >= SECOND_LIMIT){
		clock->second	= 0;
		clock->minute++;
	}
	if (clock->minute >= MINUTE_LIMIT){
		clock->minute 	= 0;
		clock->hour++;
	}
	if (clock->hour >= HOUR_LIMIT){
		clock->hour		= 0;
	}
	clock->Update(clock);
}

void Clock_Counter_Down(Clock_TypeDef* clock){
	clock->second--;
	if (clock->second < 0){
		clock->second	= SECOND_LIMIT;
		clock->minute--;
	}
	if (clock->minute < 0){
		clock->minute 	= MINUTE_LIMIT;
		clock->hour--;
	}
	if (clock->hour 	< 0){
		clock->hour		= 0;
		clock->minute 	= 0;
		clock->second 	= 0;
	}
	clock->Update(clock);
}

void Update_Clock_Buffer(Clock_TypeDef *clock){
	clock->buffer[0] 	= clock->hour 		/ DECIMAL;
	clock->buffer[1] 	= clock->hour 		% DECIMAL;
	clock->buffer[2]	= clock->minute 	/ DECIMAL;
	clock->buffer[3] 	= clock->minute 	% DECIMAL;
	clock->buffer[4]	= clock->second 	/ DECIMAL;
	clock->buffer[5] 	= clock->second 	% DECIMAL;
}


/**************************************************************************************/
/*
 * ENABLE PIN TYPE DEFINITION
 */
/**************************************************************************************/

ENPin_TypeDef * ENPin_Init(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state){
	ENPin_TypeDef * enPin = malloc(sizeof(ENPin_TypeDef));
	enPin->pin = pin;
	enPin->port = port;
	enPin->state = state;

	enPin->On = ENPin_On;
	enPin->Off = ENPin_Off;
	return enPin;
}
void ENPin_On(ENPin_TypeDef* enPin){
	enPin->state = ENABLE;
	HAL_GPIO_WritePin(enPin->port, enPin->pin, enPin->state);
}
void ENPin_Off(ENPin_TypeDef* enPin){
	enPin->state = DISABLE;
	HAL_GPIO_WritePin(enPin->port, enPin->pin, enPin->state);
}


/**************************************************************************************/
/*
 * 7 SEGMENT TYPE DEFINITION
 */
/**************************************************************************************/

static unsigned char referCode[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

SevenSeg_TypeDef * SevenSeg_Init(GPIO_TypeDef* port[], uint16_t pin[], ENPin_TypeDef * enPin){
	SevenSeg_TypeDef * sevenSeg = malloc(sizeof(SevenSeg_TypeDef));
	for (uint8_t index = 0; index < NO_OF_SEGMENT; index++){
		sevenSeg->pin[index] 	= pin[index];
		sevenSeg->port[index] 	= port[index];
		sevenSeg->state[index] 	= DISABLE;
	}
	sevenSeg->enPin 			= enPin;
	sevenSeg->Display 			= Seg_Display;
	sevenSeg->Convert 			= Number_Conversion;
	return sevenSeg;
}

void Seg_Display(SevenSeg_TypeDef * sevenSeg){
	for (uint8_t index = 0; index < NO_OF_SEGMENT; index++){
		HAL_GPIO_WritePin(sevenSeg->port[index], sevenSeg->pin[index], sevenSeg->state[index]);
	}
}

void Number_Conversion(SevenSeg_TypeDef* sevenSeg, uint8_t number){
	for (uint8_t index = 0; index < NO_OF_SEGMENT; index++){
		sevenSeg->state[index] = (referCode[number] >> index) & 0x01;
	}
}

/**************************************************************************************/
/*
 * BUTTON TYPE DEFINITION
 *
 *
 * FILTER_LEVEL - 2 is the current input
 * FILTER_LEVEL - 1 is the previous input
 * The others are filtered input
 *
 *
 */
/**************************************************************************************/

Button_TypeDef* Button_Init(GPIO_TypeDef* port, uint16_t pin, STIM_TypeDef* stim){
	Button_TypeDef* button 	= malloc(sizeof(Button_TypeDef));
	button->port 				= port;
	button->pin 				= pin;
	button->bStim				= stim;

	for (uint8_t index = 0; index < FILTER_LEVEL; index++){
		button->input[index] = RELEASED;
	}
	button->flag				= 0;
	button->Tap_Mode			= Tap_Mode;
	button->Hold_Mode			= Hold_Mode;
	return button;
}

uint8_t Stability_Check(Button_TypeDef* button){
	for(uint8_t index = 0; index < FILTER_LEVEL - 2; index++)
		button->input[index] = button->input[index + 1];
	button->input[FILTER_LEVEL - 2]		= 	HAL_GPIO_ReadPin(button->port, button->pin);
	for (uint8_t index = 0; index < FILTER_LEVEL - 2; index++){
		if (button->input[index] != button->input[index + 1])
			return 0;
	}
	return 1;
}


void Tap_Mode(Button_TypeDef* button){
	if (Stability_Check(button) == 1){
		if (button->input[FILTER_LEVEL - 1] != button->input[FILTER_LEVEL - 2]){
			button->input[FILTER_LEVEL - 1] = button->input[FILTER_LEVEL - 2];
			if (button->input[FILTER_LEVEL - 2] == PRESSED)
				button->flag = 1;
		}
	}
}


//void Hold_Mode(Button_TypeDef* button, uint16_t consecHold){
//	if (Stability_Check(button) == 1){
//		if (button->input[FILTER_LEVEL - 1] != button->input[FILTER_LEVEL - 2]){
//			button->input[FILTER_LEVEL - 1] = button->input[FILTER_LEVEL - 2];
//			if (button->input[FILTER_LEVEL - 2] == PRESSED){
//				button->flag = 1;
//				button->bStim->Set_Default(button->bStim);
//			}
//		}
//		else {
//			button->bStim->Timer_Run(button->bStim);
//			if (button->bStim->flag  == 1){
//				if (button->input[FILTER_LEVEL - 2] == PRESSED){
//					button->flag = 1;
//					button->bStim->Set_Default(button->bStim);
//				}
//			}
//		}
//	}
//}

void Hold_Mode(Button_TypeDef* button, uint16_t consecHold){
	if (Stability_Check(button) == 1){
		if (button->input[FILTER_LEVEL - 1] != button->input[FILTER_LEVEL - 2]){
			button->input[FILTER_LEVEL - 1] = button->input[FILTER_LEVEL - 2];
			if (button->input[FILTER_LEVEL - 2] == PRESSED){
				button->flag = 1;
				button->bStim->Set_Default(button->bStim);
			}
		}
		else {
			button->bStim->Timer_Run(button->bStim);
			if (button->bStim->flag  == 1){
				button->input[FILTER_LEVEL - 1] = RELEASED;
			}
		}
	}
}

/**************************************************************************************/
/*
 * TRAFFIC LIGHT TYPE DEFINITION
 */
/**************************************************************************************/

Traffic_TypeDef* Traffic_Init(GPIO_TypeDef* port[], uint16_t pin[], STIM_TypeDef* stim){
	Traffic_TypeDef* traffic 	= malloc(sizeof(Traffic_TypeDef));
	traffic->red 				= Led_Init(port[0], pin[0], DISABLE);
	traffic->yellow 			= Led_Init(port[1], pin[1], DISABLE);
	traffic->green 				= Led_Init(port[2], pin[2], DISABLE);
	traffic->state				= INIT;
	traffic->stim 				= stim;

	traffic->Shut_down			= All_Off;
	traffic->Freeze_Green		= Only_Green;
	traffic->Freeze_Red			= Only_Red;
	traffic->Freeze_Yellow		= Only_Yellow;
	traffic->Toggle_Green		= Toggle_Green;
	traffic->Toggle_Red			= Toggle_Red;
	traffic->Toggle_Yellow		= Toggle_Yellow;
	traffic->Normal_Run 		= Traffic_FSM;
	return traffic;
}

void Traffic_FSM(Traffic_TypeDef* traffic, Clock_TypeDef* clock, uint16_t r_Delay, uint16_t y_Delay, uint16_t g_Delay){
	switch(traffic->state){
		case INIT:
			traffic->Shut_down(traffic);

			traffic->state = AUTO_RED;
			traffic->stim->Set_Manual(traffic->stim, r_Delay);
			break;
		case AUTO_RED:
			traffic->Freeze_Red(traffic);

			if (traffic->stim->flag == 1){
				traffic->state = AUTO_GREEN;
				traffic->stim->Set_Manual(traffic->stim, g_Delay);
				clock->Modify(clock, 0, 0, g_Delay/1000);
			}
			break;
		case AUTO_YELLOW:
			traffic->Freeze_Yellow(traffic);

			if (traffic->stim->flag == 1){
				traffic->state = AUTO_RED;
				traffic->stim->Set_Manual(traffic->stim, r_Delay);
				clock->Modify(clock, 0, 0, r_Delay/1000);
			}
			break;
		case AUTO_GREEN:
			traffic->Freeze_Green(traffic);

			if (traffic->stim->flag == 1){
				traffic->state = AUTO_YELLOW;
				traffic->stim->Set_Manual(traffic->stim, y_Delay);
				clock->Modify(clock, 0, 0, y_Delay/1000);
			}
			break;
		case EXIT:
			traffic->Shut_down(traffic);

			traffic->state = AUTO_GREEN;
			traffic->stim->Set_Manual(traffic->stim, g_Delay);
			break;
		default:
			break;
	}
}

void All_Off(Traffic_TypeDef* traffic) {
	traffic->red->Off(traffic->red);
	traffic->yellow->Off(traffic->yellow);
	traffic->green->Off(traffic->green);
}
void Only_Red(Traffic_TypeDef* traffic) {
	traffic->red->On(traffic->red);
	traffic->yellow->Off(traffic->yellow);
	traffic->green->Off(traffic->green);
}
void Only_Yellow(Traffic_TypeDef* traffic) {
	traffic->red->Off(traffic->red);
	traffic->yellow->On(traffic->yellow);
	traffic->green->Off(traffic->green);
}
void Only_Green(Traffic_TypeDef* traffic) {
	traffic->red->Off(traffic->red);
	traffic->yellow->Off(traffic->yellow);
	traffic->green->On(traffic->green);
}
void Toggle_Red(Traffic_TypeDef* traffic){
	traffic->red->Toggle(traffic->red);
	traffic->yellow->Off(traffic->yellow);
	traffic->green->Off(traffic->green);
}
void Toggle_Yellow(Traffic_TypeDef* traffic){
	traffic->red->Off(traffic->red);
	traffic->yellow->Toggle(traffic->yellow);
	traffic->green->Off(traffic->green);
}
void Toggle_Green(Traffic_TypeDef* traffic){
	traffic->red->Off(traffic->red);
	traffic->yellow->Off(traffic->yellow);
	traffic->green->Toggle(traffic->green);
}
