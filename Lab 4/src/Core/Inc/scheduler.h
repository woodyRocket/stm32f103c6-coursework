/*
 * scheduler.h
 *
 *  Created on: Nov 16, 2022
 *      Author: ttrng
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "component.h"
#include "stim_manip.h"

#define MAX_TASK		10
#define NO_OF_LED 		3
#define NO_OF_TASK 		3
#define RETURN_NORMAL	1
#define RETURN_ERROR	0
#define SCH_TOO_MANY_TASKS			10
#define	SCH_NO_TASK_FOUND			20

typedef struct Task{

	uint16_t delay;
	uint16_t period;
	uint16_t running;
	uint16_t id;

	void (*Run) (void);

}Task_TypeDef;

typedef struct TaskPQueue{
	Task_TypeDef* task;
	uint16_t maxSize;
	uint16_t count;

	uint8_t (*Is_Empty)(struct TaskPQueue* pq);
}PQueue_TypeDef;

Task_TypeDef* Task_Init(uint16_t delay, uint16_t period, void (*Function)(void));
void Copy(Task_TypeDef* task1, Task_TypeDef* task2);

PQueue_TypeDef* TaskPQ_Init(void);
uint8_t Is_Empty(PQueue_TypeDef* pq);
void SCH_Update(PQueue_TypeDef* pq);
void SCH_Dispatch_Tasks(PQueue_TypeDef* pq);
uint16_t SCH_Add_Task(PQueue_TypeDef* pq, void (*function)(void), uint32_t delay, uint32_t period);
uint8_t SCH_Delete_Task(PQueue_TypeDef* pq, uint32_t id);

void Build_PQueue(PQueue_TypeDef* pq, Task_TypeDef* taskArray, uint16_t count, uint16_t maxSize);

void MultiLed_Init(void);
void Parameter_Init(void);

void Turn_On_Red(void);
void Turn_On_Yellow(void);
void Turn_On_Green(void);
void Toggle_Led(void);

extern PQueue_TypeDef* taskQueue;
extern uint16_t redCounter;
extern uint16_t yellowCounter;
extern uint16_t greenCounter;

#endif /* INC_SCHEDULER_H_ */
