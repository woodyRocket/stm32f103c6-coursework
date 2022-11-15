/*
 * button_manip.h
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */

#ifndef INC_BUTTON_MANIP_H_
#define INC_BUTTON_MANIP_H_

#include "component.h"
#include "stim_manip.h"

#define NO_OF_BUTTON			3

extern Button_TypeDef* buttonMode;
extern Button_TypeDef* buttonTime;
extern Button_TypeDef* buttonSet;

void Traffic_Button_Init(void);
void Button_Scan(void);

#endif /* INC_BUTTON_MANIP_H_ */
