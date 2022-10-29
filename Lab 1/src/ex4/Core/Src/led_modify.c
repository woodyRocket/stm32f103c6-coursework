/*
 * led_modify.c
 *
 *  Created on: Oct 26, 2022
 *      Author: ttrng
 */

#include "led_modify.h"
#include "gpio.h"
#include "software_timer.h"

enum LED status = YELLOW;

static uint32_t redOnCounter, yellowOnCounter, greenOnCounter;

static uint32_t dynamicRedCounter 			= 0;
static uint32_t dynamicYellowCounter 		= 0;
static uint32_t dynamicGreenCounter 		= 0;

void LED_Setup(uint32_t redOnTime, uint32_t yellowOnTime, uint32_t greenOnTime){
        redOnCounter 	= 	redOnTime;
        yellowOnCounter =	yellowOnTime;
        greenOnCounter 	= 	greenOnTime;
}

void LED_Alternating(void){
    switch (status)
    {
    case RED:
        if (++dynamicRedCounter < redOnCounter)
        {
            status = RED;
            Turn_On_Red();
            Turn_Off_Yellow();
            Turn_Off_Green();
        }
        else
        {
            status = YELLOW;
            dynamicRedCounter = 0;
        }
        break;
    case YELLOW:
        if (++dynamicYellowCounter < yellowOnCounter)
        {
            status = YELLOW;
            Turn_On_Yellow();
            Turn_Off_Red();
            Turn_Off_Green();
        }
        else
        {
            status = GREEN;
            dynamicYellowCounter = 0;
        }
        break;

    case GREEN:
        if (++dynamicGreenCounter < greenOnCounter)
        {
            status = GREEN;
            Turn_On_Green();
            Turn_Off_Red();
            Turn_Off_Yellow();
        }
        else
        {
            status = RED;
            dynamicGreenCounter = 0;
        }
        break;
    default:
    	break;
    }
}

