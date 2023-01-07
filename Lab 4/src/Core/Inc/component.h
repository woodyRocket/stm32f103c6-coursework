/*
 * component.h
 *
 *  Created on: Nov 4, 2022
 *      Author: ttrng
 */

#ifndef INC_COMPONENT_H_
#define INC_COMPONENT_H_

#include "stdint.h"
#include "stdlib.h"
#include "main.h"

#define DECIMAL						10
#define TIME_DIGITS					6
#define HOUR_LIMIT 					24
#define MINUTE_LIMIT				60
#define SECOND_LIMIT				60
#define NO_OF_SEGMENT 				7
#define FILTER_LEVEL				4
#define RELEASED					GPIO_PIN_SET
#define PRESSED						GPIO_PIN_RESET
#define ENABLE						GPIO_PIN_RESET
#define DISABLE						GPIO_PIN_SET


/**************************************************************************************/
/*
 * SOFTWARE TIMER TYPE DEFINITION
 */
/**************************************************************************************/

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

typedef struct Software_TIM{
	uint16_t delay;
	uint16_t interrupt;
	uint16_t counter;
	uint8_t flag;

	void (*Set_Default)(struct Software_TIM* stim);
	void (*Set_Manual)(struct Software_TIM* stim, uint16_t delay);
	void (*Timer_Run)(struct Software_TIM* stim);
}STIM_TypeDef;

STIM_TypeDef * STIM_Init(uint16_t delay, uint16_t interrupt);
void STIM_Set_Default(STIM_TypeDef* stim);
void STIM_Set_Manual(STIM_TypeDef* stim, uint16_t delay);
void STIM_Timer_Run(STIM_TypeDef* stim);

#endif


/**************************************************************************************/
/*
 * LED TYPE DEFINITION
 */
/**************************************************************************************/

#ifndef INC_LED_H_
#define INC_LED_H_

typedef struct Led_Status{
	GPIO_TypeDef * port;
	uint16_t pin;
	GPIO_PinState state;

	void (*Display)(struct Led_Status* led);
	void (*Toggle)(struct Led_Status* led);
	void (*On)(struct Led_Status* led);
	void (*Off)(struct Led_Status* led);
}LED_TypeDef;

LED_TypeDef * Led_Init(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state);
void Led_Display(LED_TypeDef* led);
void Led_Toggle(LED_TypeDef* led);
void Led_On(LED_TypeDef* led);
void Led_Off(LED_TypeDef* led);

void Display_Led(LED_TypeDef* led);
#endif /* INC_LED_H_ */


/**************************************************************************************/
/*
 * CLOCK TYPE DEFINTION
 */
/**************************************************************************************/

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

typedef struct Clock_Status{
	int8_t hour;
	int8_t minute;
	int8_t second;
	int8_t buffer[TIME_DIGITS];

	void (*Modify)(struct Clock_Status* clock, uint8_t hour, uint8_t minute, uint8_t second);
	void (*Up)(struct Clock_Status* clock);
	void (*Down)(struct Clock_Status* clock);
	void (*Update)(struct Clock_Status* clock);
}Clock_TypeDef;

Clock_TypeDef* Clock_Init(uint8_t hour, uint8_t minute, uint8_t second);
void Time_Modify(Clock_TypeDef* clock, uint8_t hour, uint8_t minute, uint8_t second);
void Clock_Counter_Up(Clock_TypeDef* clock);
void Clock_Counter_Down(Clock_TypeDef* clock);
void Update_Clock_Buffer(Clock_TypeDef* clock);

#endif /* INC_CLOCK_H_ */



/**************************************************************************************/
/*
 * ENABLE PIN TYPE DEFINITION
 */
/**************************************************************************************/

#ifndef INC_ENABLE_PIN_H_
#define INC_ENABLE_PIN_H_

typedef struct ENPin_Status{
	uint16_t pin;
	GPIO_TypeDef* port;
	GPIO_PinState state;

	void (*On)(struct ENPin_Status* enPin);
	void (*Off)(struct ENPin_Status* enPin);
}ENPin_TypeDef;

ENPin_TypeDef * ENPin_Init(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state);
void ENPin_On(ENPin_TypeDef* enPin);
void ENPin_Off(ENPin_TypeDef* enPin);

#endif /* INC_ENABLE_PIN_H_ */

/**************************************************************************************/
/*
 * 7 SEGMENT TYPE DEFINITION
 */
/**************************************************************************************/
#ifndef INC_7SEG_H_
#define INC_7SEG_H_

typedef struct SevenSeg_Status{
	uint16_t pin[NO_OF_SEGMENT];
	GPIO_TypeDef* port[NO_OF_SEGMENT];
	GPIO_PinState state[NO_OF_SEGMENT];
	ENPin_TypeDef * enPin;

	void (*Display)(struct SevenSeg_Status* sevenSeg);
	void (*Convert)(struct SevenSeg_Status* sevenSeg, uint8_t number);
}SevenSeg_TypeDef;

SevenSeg_TypeDef * SevenSeg_Init(GPIO_TypeDef* port[], uint16_t pin[], ENPin_TypeDef * enPin);
void Seg_Display(SevenSeg_TypeDef * sevenSeg);
void Number_Conversion(SevenSeg_TypeDef* sevenSeg, uint8_t number);

#endif /* INC_7SEG_H_ */

/**************************************************************************************/
/*
 * BUTTON TYPE DEFINITION
 */
/**************************************************************************************/
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


typedef struct Button_Status{
	uint16_t pin;
	GPIO_TypeDef* port;
	STIM_TypeDef* bStim;

	GPIO_PinState input[FILTER_LEVEL];
	uint8_t flag;

	void (*Tap_Mode)(struct Button_Status* button);
	void (*Hold_Mode)(struct Button_Status* button, uint16_t consecHold);

}Button_TypeDef;

Button_TypeDef* Button_Init(GPIO_TypeDef* port, uint16_t pin, STIM_TypeDef* stim);
void Tap_Mode(Button_TypeDef* button);
void Hold_Mode(Button_TypeDef* button, uint16_t consecHold);

#endif /* INC_BUTTON_H_ */

/**************************************************************************************/
/*
 * TRAFFIC LIGHT TYPE DEFINITION
 */
/**************************************************************************************/
#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

typedef enum TL_State {
	INIT,
	AUTO_RED,
	AUTO_YELLOW,
	AUTO_GREEN,
	EXIT
}TrafficState;

typedef struct Traffic_Status{
	LED_TypeDef * red;
	LED_TypeDef * yellow;
	LED_TypeDef * green;
	STIM_TypeDef * stim;
	TrafficState state;

	void (*Normal_Run)(struct Traffic_Status * traffic, Clock_TypeDef* clock, uint16_t r_Delay, uint16_t y_Delay, uint16_t g_Delay);
	void (*Shut_down)(struct Traffic_Status* traffic);
	void (*Freeze_Red)(struct Traffic_Status* traffic);
	void (*Freeze_Yellow)(struct Traffic_Status* traffic);
	void (*Freeze_Green)(struct Traffic_Status* traffic);
	void (*Toggle_Red)(struct Traffic_Status* traffic);
	void (*Toggle_Yellow)(struct Traffic_Status* traffic);
	void (*Toggle_Green)(struct Traffic_Status* traffic);
}Traffic_TypeDef;

Traffic_TypeDef* Traffic_Init(GPIO_TypeDef* port[], uint16_t pin[], STIM_TypeDef* stim);
void Traffic_FSM(Traffic_TypeDef * traffic, Clock_TypeDef* clock, uint16_t r_Delay, uint16_t y_Delay, uint16_t g_Delay);
void All_Off(Traffic_TypeDef* traffic);
void Only_Red(Traffic_TypeDef* traffic);
void Only_Yellow(Traffic_TypeDef* traffic);
void Only_Green(Traffic_TypeDef* traffic);
void Toggle_Red(Traffic_TypeDef* traffic);
void Toggle_Yellow(Traffic_TypeDef* traffic);
void Toggle_Green(Traffic_TypeDef* traffic);

#endif /* INC_TRAFFIC_LIGHT_H_ */


/**************************************************************************************/
/*
 * SCHEDULER TYPE DEFINITION
 */
/**************************************************************************************/
//#ifndef INC_SCHEDULER_H_
//#define INC_SCHEDULER_H_
//
//typedef struct Task{
//
//}Task_TypeDef;
//
//#endif /*INC_SCHEDULER_H_*/

#endif /* INC_COMPONENT_H_ */
