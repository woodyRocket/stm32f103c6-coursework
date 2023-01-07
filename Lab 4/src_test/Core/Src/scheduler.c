/*
 * scheduler.c
 *
 *  Created on: Nov 27, 2022
 *      Author: MSI
 */

#include "main.h"
#include "scheduler.h"

typedef struct {
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void);
	// Delay (ticks) until the function will ( next ) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs .
	uint32_t Period;
	// Incremented ( by scheduler ) when task i s due to execute
	uint8_t RunMe;
	// This i s a hint to solve the question below .
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 10
#define NO_TASK_ID 0

sTask SCH_tasks_G [SCH_MAX_TASKS ];

unsigned char Error_code_G = 0;
int numberOfTasks = 0;

void SCH_Init(void){
	unsigned char i;
	for ( i = 0; i < SCH_MAX_TASKS; i ++) {
		SCH_Delete_Task ( i ) ;
	}
	// Reset the global error variable
	// − SCH_Delete_Task() will generate an error code ,
	// ( because the task array i s empty)
	Error_code_G = 0;
}

void SCH_Update(void){
	unsigned char Index = 0;
		// NOTE: calculations are in *TICKS* ( not milliseconds )
	if (SCH_tasks_G[Index].pTask) {
		if (SCH_tasks_G[Index].Delay == 0) {
			// The task i s due to run
			// Inc . the ’RunMe’ flag
			SCH_tasks_G[Index].RunMe += 1;
		} else {
			// Not yet ready to run : just decrement the delay
			SCH_tasks_G[Index].Delay -= 1;
		}
	}
}

uint32_t SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD){
	if (numberOfTasks == SCH_MAX_TASKS)
		return 0; // no more place
	unsigned char Index = 0;
	while (1) {
		if (Index == numberOfTasks)
			break;
		if (DELAY < SCH_tasks_G[Index].Delay)
			break;
		DELAY -= SCH_tasks_G[Index].Delay;
		Index++;
	}
	for (int i = numberOfTasks; i > Index; i--) {
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
		//SCH_tasks_G[i].Delay -= DELAY;
	}
	if(Index != numberOfTasks)
		SCH_tasks_G[Index+1].Delay -= DELAY;	// if the position Index point to is not the last one, update DELAY of the right-follower of out input place

	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	// return position of task ( to allow later deletion )
	numberOfTasks++;
	return Index;
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	//unsigned char Return_code ;
	if (numberOfTasks == 0)
		return 0;
	for (int i = 0; i < numberOfTasks - 1; i++) {
		SCH_tasks_G[i] = SCH_tasks_G[i + 1];
	}
	numberOfTasks--;
	SCH_tasks_G[numberOfTasks].pTask = 0x0000;
	SCH_tasks_G[numberOfTasks].Delay = 0;
	SCH_tasks_G[numberOfTasks].Period = 0;
	SCH_tasks_G[numberOfTasks].RunMe = 0;
	//return Return_code; // return status
	return 0;
}

void SCH_Dispatch_Tasks(void) {
	unsigned char Index = 0;
	// Dispatches ( runs ) the next task ( if one is ready )
	//for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
	if (SCH_tasks_G[Index].RunMe > 0) {
		(*SCH_tasks_G[Index].pTask)(); // Run the task
		SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
		// Periodic tasks w ill automatically run again if this is a ’one shot’ task , remove it from the array
		if (SCH_tasks_G[Index].Period == 0) {
			SCH_Delete_Task(Index);
		} else {
			sTask temp = SCH_tasks_G[Index];
			SCH_Delete_Task(Index);
			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
		}
	}
	// Report system status
	// SCH_Report_Status();
	// The scheduler enters idle mode at this point
	SCH_Go_To_Sleep();
}

void SCH_Go_To_Sleep(void){
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
