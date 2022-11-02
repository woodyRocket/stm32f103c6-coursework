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

void Turn_On_Led(unsigned char pos){
	HAL_GPIO_WritePin(ledPort[pos], ledPin[pos], ENABLE);
}

void Turn_Off_Led(unsigned char pos){
	HAL_GPIO_WritePin(ledPort[pos], ledPin[pos], DISABLE);
}

void Display_LED_Buffer(void){
	for (unsigned char index = 0; index < NO_OF_LED; index++){
		HAL_GPIO_WritePin(ledPort[index], ledPin[index], ledBuffer[index]);
	}
}
