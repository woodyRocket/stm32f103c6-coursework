/*
 * 7_segments.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "7_segments.h"

static uint16_t segmentPin[NO_OF_SEGMENT] =
{
		SEG0_Pin,
		SEG1_Pin,
		SEG2_Pin,
		SEG3_Pin,
		SEG4_Pin,
		SEG5_Pin,
		SEG6_Pin
};

static GPIO_TypeDef * segmentPort[NO_OF_SEGMENT] =
{
		SEG0_GPIO_Port,
		SEG1_GPIO_Port,
		SEG2_GPIO_Port,
		SEG3_GPIO_Port,
		SEG4_GPIO_Port,
		SEG5_GPIO_Port,
		SEG6_GPIO_Port
};

static GPIO_PinState segmentBuffer[NO_OF_SEGMENT] =
{
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE,
		DISABLE
};

static unsigned char referCode[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};


void Display_7SEG_Buffer(void){
	for (unsigned char index = 0; index < NO_OF_SEGMENT; index++){
		HAL_GPIO_WritePin(segmentPort[index], segmentPin[index], segmentBuffer[index]);
	}
}

void Number_Conversion(unsigned char number){
	for (unsigned char index = 0; index < NO_OF_SEGMENT; index++){
		segmentBuffer[index] = referCode[number] >> index & 0x01;
	}
}

void Segment_Processing(void){
	Switching_Pin();
	static unsigned char internalCounter = 0;
	switch(enableFlag[internalCounter]){
		case ENABLE:
			Number_Conversion(timeBuffer[internalCounter]);
			Display_7SEG_Buffer();
			break;
		default:
			break;
	}
	internalCounter = (internalCounter + 1) % NO_OF_7SEG_DEVICE;
}
