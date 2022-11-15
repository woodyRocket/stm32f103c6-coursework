/*
 * traffic_light.h
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */

#ifndef INC_TRAFFIC_MANIP_H_
#define INC_TRAFFIC_MANIP_H_

#include "component.h"
#include "stim_manip.h"
#include "7seg_manip.h"

//#define V_RED_TIME			6000
//#define V_YELLOW_TIME			2000
//#define V_GREEN_TIME			3000

#define H_RED_TIME_EX				5000
#define H_YELLOW_TIME_EX			2000
#define H_GREEN_TIME_EX				4000


extern uint16_t V_RED_TIME;
extern uint16_t V_YELLOW_TIME;
extern uint16_t V_GREEN_TIME;
extern uint16_t H_YELLOW_TIME;
extern uint16_t H_RED_TIME;
extern uint16_t H_GREEN_TIME;
extern Traffic_TypeDef* vTrafficLight;
extern Traffic_TypeDef* hTrafficLight;
extern Clock_TypeDef *	vClock;
extern Clock_TypeDef *	hClock;

void Sub_Road(uint16_t mainRed, uint16_t mainYellow, uint16_t mainGreen);
void Main_Road(uint16_t subRed, uint16_t subYellow, uint16_t subGreen);
void Intersection_Init(void);
void Intersection_Normal_Mode(void);
void Vertical_Normal_Mode(void);
void Horizontal_Normal_Mode(void);
#endif /* INC_TRAFFIC_MANIP_H_ */
