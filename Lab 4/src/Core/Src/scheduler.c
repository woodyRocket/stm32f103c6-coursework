/*
 * scheduler.c
 *
 *  Created on: Nov 16, 2022
 *      Author: ttrng
 */


#include "scheduler.h"

/**************************************************************************************/
/*
 * TASK TYPE DEFINITION
 */
/**************************************************************************************/
unsigned char error_code = 0;

Task_TypeDef* Task_Init(uint16_t delay, uint16_t period, void (*Function)(void)){
	Task_TypeDef* task 	= malloc(sizeof(Task_TypeDef));
	task->delay 		= delay;
	task->period 		= period;
	task->running 		= 0;
	task->id 			= 0;

	task->Run 			= Function;
	return task;
}

PQueue_TypeDef* TaskPQ_Init(void){
	PQueue_TypeDef* pq 			= malloc(sizeof(PQueue_TypeDef));
	pq->maxSize					= MAX_TASK;
	pq->count 					= 0;

	pq->Is_Empty 				= Is_Empty;
	return pq;
}

void Copy(Task_TypeDef* task1, Task_TypeDef* task2){
	task1->delay 	= task2->delay;
	task1->period 	= task2->period;
	task1->id 		= task2->id;
	task1->running 	= task2->running;
	task1->Run 		= task2->Run;
}

static void swap(Task_TypeDef array[], uint16_t i , uint16_t j){
	Task_TypeDef temp;
	Copy(&temp, &array[i]);
	Copy(&array[i], &array[j]);
	Copy(&array[j], &temp);
}
uint8_t Is_Leaf(PQueue_TypeDef* pq, uint16_t position){
	if ((position >= pq->count/2) && (position < pq->count))
		return 1;
	return 0;
}
static uint16_t Left_Child(uint16_t position){
	return 2*position + 1;
}
static uint16_t Right_Child(uint16_t position){
	return 2*position + 2;
}
static uint16_t Parent(uint16_t position){
	return (position - 1)/2;
}
static void Heap_Down(PQueue_TypeDef* pq, uint16_t pos){
	while(Is_Leaf(pq, pos) != 0){
		uint16_t lc = Left_Child(pos);
		uint16_t rc = Right_Child(pos);
		if ((rc < pq->count) && (pq->task[rc].period < pq->task[lc].period)){
			lc = rc;
		}
		if (pq->task[pos].period < pq->task[lc].period)
			return;
		swap(pq->task, pos, lc);
		pos = lc;
	}
}
static void Heap_Up(PQueue_TypeDef* pq, uint16_t pos){
	while((pos != 0) && pq->task[pos].period < pq->task[Parent(pos)].period){
		swap(pq->task, pos, Parent(pos));
		pos = Parent(pos);
	}
}

void Build_PQueue(PQueue_TypeDef* pq, Task_TypeDef* taskArray, uint16_t count, uint16_t maxSize){
	pq->task 	= taskArray;
	pq->count 	= count;
	pq->maxSize = maxSize;
	for (uint16_t index = pq->count /2 - 1; index >= 0; index--){
		Heap_Down(pq, index);
	}
}

uint8_t Is_Empty(PQueue_TypeDef* pq){
	if (pq->count == 0)
		return 1;
	return 0;
}
uint16_t SCH_Add_Task(PQueue_TypeDef* pq, void (*Function)(void), uint32_t delay, uint32_t period){
	Task_TypeDef* newTask = Task_Init(delay, period, Function);
	if (pq->count >= pq->maxSize){
		error_code = SCH_TOO_MANY_TASKS;
		return error_code;
	}
	else{
		newTask->id = pq->count;
		uint16_t position = pq->count++;

		pq->task[position] = *newTask;
		Heap_Up(pq, position);
		return newTask->id;
	}
}

uint8_t SCH_Delete_Task(PQueue_TypeDef* pq, uint32_t id){
	unsigned char returnCode;
	for (uint16_t index = 0; index < pq->count; index++){
		if (pq->task[index].id == id){
			returnCode = RETURN_NORMAL;

			pq->task[index].Run 	= NULL;
			pq->task[index].delay 	= 0;
			pq->task[index].running = 0;
			pq->task[index].period 	= 0;
		}
		else
			returnCode = RETURN_ERROR;
	}
	return returnCode;
}

///add_task(runsomething, 300, 1000)
void SCH_Update(PQueue_TypeDef* pq){
	uint16_t index;
	for (index = 0; index < pq->maxSize; index++){
		if (pq->task[index].Run != NULL){
			if (pq->task[index].delay == 0){
				pq->task[index].running += 1;
				if (pq->task[index].period != 0){
					pq->task[index].delay = pq->task[index].period;
				}
			}
			else {
				pq->task[index].delay--;
			}
		}
	}
}
void SCH_Dispatch_Tasks(PQueue_TypeDef* pq){
	uint16_t index;
	for (index = 0; index < pq->maxSize; index++){
		if(pq->task[index].running > 0){
			(*pq->task[index].Run)();
			pq->task[index].running --;
			if (pq->task[index].period == 0)
				SCH_Delete_Task(pq, pq->task[index].id);
		}
	}
}


/**************************************************************************************/

const uint16_t redTime 		= 5000;
const uint16_t yellowTime 	= 2000;
const uint16_t greenTime 	= 3000;


uint16_t ledPin[NO_OF_LED] = {
		LED_RED_Pin,
		LED_YELLOW_Pin,
		LED_GREEN_Pin
};


GPIO_TypeDef* ledPort[NO_OF_LED] = {
		LED_RED_GPIO_Port,
		LED_YELLOW_GPIO_Port,
		LED_GREEN_GPIO_Port
};


LED_TypeDef* red;
LED_TypeDef* yellow;
LED_TypeDef* green;

uint16_t redCounter;
uint16_t yellowCounter;
uint16_t greenCounter;

PQueue_TypeDef* taskQueue;


void Turn_On_Red(void){
	Led_On(red);
	Led_Off(yellow);
	Led_Off(green);
}

void Turn_On_Yellow(void){
	Led_Off(red);
	Led_On(yellow);
	Led_Off(green);
}

void Turn_On_Green(void){
	Led_Off(red);
	Led_Off(yellow);
	Led_On(green);
}

void Parameter_Init(void){
	redCounter 			= redTime		/TIM2_TIMER_INTERRUPT;
	yellowCounter 		= yellowTime	/TIM2_TIMER_INTERRUPT;
	greenCounter 		= greenTime		/TIM2_TIMER_INTERRUPT;
}

void MultiLed_Init(void){
	red = Led_Init(ledPort[0], ledPin[0], DISABLE);
	yellow = Led_Init(ledPort[1], ledPin[1], DISABLE);
	green = Led_Init(ledPort[2], ledPin[2], DISABLE);
}

void Toggle_Led(void){
	green->Toggle(green);
}






