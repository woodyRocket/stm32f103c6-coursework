/*
 * led_modify.h
 *
 *  Created on: Oct 31, 2022
 *      Author: ttrng
 */

#ifndef INC_LED_MODIFY_H_
#define INC_LED_MODIFY_H_

#include "main.h"

#define NO_OF_LED		1

void Turn_On_Led(unsigned char pos);
void Turn_Off_Led(unsigned char pos);
void Display_LED_Buffer(void);

#endif /* INC_LED_MODIFY_H_ */
