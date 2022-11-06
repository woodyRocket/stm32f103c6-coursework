/*
 * 7_segments.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "7seg_manip.h"

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

static uint8_t stateBuffer[DECIMAL]  = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static uint8_t currentState;
static uint8_t inCounter = 0;

SevenSeg_TypeDef* sevenSeg;

void SevenSEG_Init(void){
	sevenSeg = SevenSeg_Init(segmentPort, segmentPin, NULL);
}
void Update_State(void){
	currentState = stateBuffer[inCounter];
	inCounter = (inCounter + 1) % DECIMAL;
}

void SevenSEG_Display(void){
	sevenSeg->Convert(sevenSeg, currentValue);
	sevenSeg->Display(sevenSeg);
}

