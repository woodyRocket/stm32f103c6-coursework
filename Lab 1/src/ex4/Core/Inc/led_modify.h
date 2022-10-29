/*
 * led_modify.h
 *
 *  Created on: Oct 26, 2022
 *      Author: ttrng
 */

#ifndef INC_LED_MODIFY_H_
#define INC_LED_MODIFY_H_

#include <stdint.h>

enum LED
{
    RED,
    YELLOW,
	GREEN

};

void LED_Setup(uint32_t redOnTime, uint32_t yellowOnTime, uint32_t greenOnTime);
void LED_Alternating(void);
#endif /* INC_LED_MODIFY_H_ */
