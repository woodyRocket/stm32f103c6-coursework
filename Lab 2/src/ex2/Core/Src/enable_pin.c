/*
 * signal_pin.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "enable_pin.h"

static uint16_t enablePin[NO_OF_7SEG_DEVICE] =
{
		EN0_Pin,
		EN1_Pin,
		EN2_Pin,
		EN3_Pin
};

static GPIO_TypeDef * enablePort[NO_OF_7SEG_DEVICE] =
{
		EN0_GPIO_Port,
		EN1_GPIO_Port,
		EN2_GPIO_Port,
		EN3_GPIO_Port
};

static GPIO_PinState enablePinBuffer[NO_OF_7SEG_DEVICE] =
{
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE
};

unsigned char enableFlag[NO_OF_7SEG_DEVICE] =
{
		0,
		0,
		0,
		0
};

void Display_EN_Buffer(void){
	for (unsigned char index = 0; index < NO_OF_7SEG_DEVICE; index++){
		HAL_GPIO_WritePin(enablePort[index], enablePin[index], enablePinBuffer[index]);
	}
}
void Pin_Init(unsigned char pos){
	if (pos < 0 || pos >= NO_OF_7SEG_DEVICE) return;
	else{
		enablePinBuffer[pos] = ENABLE;
		for (unsigned char index = 0; index < NO_OF_7SEG_DEVICE; index++){
			if (index != pos)
				enablePinBuffer[index] = DISABLE;
		}
	}
}
void Switching_Pin(void){
	static unsigned char pinIndex 	= 0;
	Pin_Init(pinIndex);
	Display_EN_Buffer();
	pinIndex = (pinIndex + 1) % NO_OF_7SEG_DEVICE;
}
