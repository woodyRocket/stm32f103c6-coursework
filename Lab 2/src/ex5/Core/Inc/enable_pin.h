/*
 * enable_signal.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_ENABLE_PIN_H_
#define INC_ENABLE_PIN_H_

#include "7_segments.h"
#include "main.h"

extern unsigned char enableFlag[];

void Display_EN_Buffer(void);
void Pin_Init(unsigned char pos);
void Switching_Pin(void);

#endif /* INC_ENABLE_PIN_H_ */
