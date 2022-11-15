/*
 * mode.h
 *
 *  Created on: Nov 13, 2022
 *      Author: ttrng
 */

#ifndef INC_MODE_H_
#define INC_MODE_H_

#include "button_manip.h"
#include "traffic_manip.h"
#include "stim_manip.h"

#define NO_OF_MODE		5
#define UPPERBOUND		100000
typedef enum MODE{
	NORMAL,
	RED_MOD,
	YELLOW_MOD,
	GREEN_MOD,
	EXIT_MOD
}MODE_STATE;

void ModeButton_Pressed(void);
void Mode_Processing(void);


#endif /* INC_MODE_H_ */
