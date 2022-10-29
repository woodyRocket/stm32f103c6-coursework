/*
 * 7_segment.c
 *
 *  Created on: Oct 27, 2022
 *      Author: ttrng
 */

#include "7_segment.h"
#include "gpio.h"

static GPIO_TypeDef * segmentPort[NUMBER_OF_SEGMENT] =
{
		SEG_A_GPIO_Port,
		SEG_B_GPIO_Port,
		SEG_C_GPIO_Port,
		SEG_D_GPIO_Port,
		SEG_E_GPIO_Port,
		SEG_F_GPIO_Port,
		SEG_G_GPIO_Port
};

static uint16_t segmentPin[NUMBER_OF_SEGMENT] =
{
		SEG_A_Pin,
		SEG_B_Pin,
		SEG_C_Pin,
		SEG_D_Pin,
		SEG_E_Pin,
		SEG_F_Pin,
		SEG_G_Pin
};

static uint8_t referCode[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
static uint8_t internalCounter = 0;

void Display_Number(uint8_t codeIndex){
	for (uint8_t index = 0; index < NUMBER_OF_SEGMENT; index++){
		Data_Out(segmentPort[index], segmentPin[index], (referCode[codeIndex] >> index & 0x01));
	}
}

void Seg_Setup(uint8_t counter){
	if (counter < 0 || counter >= DECIMAL_COUNTER) return;
	internalCounter = counter;

}

void Display_7Seg(void){
	if (internalCounter <= 0){
		Display_Number(0);
	}
	else {
		Display_Number(internalCounter);
		internalCounter--;
	}
}

