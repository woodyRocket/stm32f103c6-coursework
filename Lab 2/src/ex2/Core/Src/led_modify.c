/*
 * led_modify.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#include "led_modify.h"

static uint16_t ledPin[NO_OF_LED] =
{
		LED0_Pin
};

static GPIO_TypeDef * ledPort[NO_OF_LED] =
{
		LED0_GPIO_Port
};

static GPIO_PinState ledBuffer[NO_OF_LED] =
{
		DISABLE
};

static uint16_t dotPin[LED_DOT] =
{
		DOT_Pin
};

static GPIO_TypeDef * dotPort[LED_DOT] =
{
		DOT_GPIO_Port
};

void Display_LED_Buffer(void){
	for (unsigned char index = 0; index < NO_OF_LED; index++){
		HAL_GPIO_WritePin(ledPort[index], ledPin[index], ledBuffer[index]);
	}
}
void Display_Dot_Buffer(void){
	for (unsigned char index = 0; index < LED_DOT; index++){
		HAL_GPIO_TogglePin(dotPort[index], dotPin[index]);
	}
}
