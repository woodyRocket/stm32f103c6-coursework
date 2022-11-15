/*
 * 7_segments.c
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */


#include "7seg_manip.h"

static uint16_t enPin[2*NO_OF_7SEG_DEVICE] =
{
		EN0_Pin,
		EN1_Pin,
		EN2_Pin,
		EN3_Pin
};

static GPIO_TypeDef * enPort[2*NO_OF_7SEG_DEVICE] =
{
		EN0_GPIO_Port,
		EN1_GPIO_Port,
		EN2_GPIO_Port,
		EN3_GPIO_Port
};

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

static uint8_t vBuffer[NO_OF_7SEG_DEVICE];
static uint8_t hBuffer[NO_OF_7SEG_DEVICE];

SevenSeg_TypeDef* SevenSeg[2*NO_OF_7SEG_DEVICE];


void Intersection_7SEG_Init(void){
	vBuffer[0] = vClock->buffer[4];
	vBuffer[1] = vClock->buffer[5];
	hBuffer[0] = hClock->buffer[4];
	hBuffer[1] = hClock->buffer[5];

	for (uint8_t index = 0; index < 2*NO_OF_7SEG_DEVICE; index++){
		SevenSeg[index] = SevenSeg_Init(segmentPort, segmentPin,
				ENPin_Init(enPort[index], enPin[index], DISABLE));
	}
}

void Segment_To_Buffer(void){
	vBuffer[0] = vClock->buffer[4];
	vBuffer[1] = vClock->buffer[5];
	hBuffer[0] = hClock->buffer[4];
	hBuffer[1] = hClock->buffer[5];

	for(uint8_t index = 0; index < NO_OF_7SEG_DEVICE; index++){
		SevenSeg[index]->Convert(SevenSeg[index], hBuffer[index]);
		SevenSeg[index + NO_OF_7SEG_DEVICE]->Convert(SevenSeg[index + NO_OF_7SEG_DEVICE], vBuffer[index]);
	}
}
void Intersection_7SEG_Display(void){
	Segment_To_Buffer();
	static uint8_t counter = 0;
	SevenSeg[counter]->enPin->On(SevenSeg[counter]->enPin);
	for (uint8_t index = 0; index < 2*NO_OF_7SEG_DEVICE; index++){
		if (index != counter)
			SevenSeg[index]->enPin->Off(SevenSeg[index]->enPin);
	}
	SevenSeg[counter]->Display(SevenSeg[counter]);
	counter = (counter + 1) % (2* NO_OF_7SEG_DEVICE);
}

