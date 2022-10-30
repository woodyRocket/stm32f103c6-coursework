//#define 	DELAY_TIME 		10
void LedOperationProcessing(void);
void LedInit(uint32_t onTime, uint32_t offTime);
void TurnLedOn(void);
void TurnLedOff(void);

enum LedState {LED_ON, LED_OFF};

enum LedState ledState = LED_ON;


const uint8_t delayTime = 10
static uint32_t ledOnTime, ledOffTime;


//onTime offTime in second
void Led_Setup(uint32_t onTime, uint32_t offTime){
	if(delayTime != 0){
		ledOnTime = onTime*1000/DELAY_TIME;
		ledOffTime = offTime*1000/DELAY_TIME;
	}
}
void TurnLedOn(void){
	HAL_WritePin(portled, pinled, RESET);
}

void TurnLedOff(void){
	HAL_WritePin(portled, pinled, SET);
}

void Led_Operation_Processing(void){
	static uint32_t ledCounter = 0;
	ledCounter ++;
	switch (ledState){
		case LED_ON: //0 --> 0n
			if(ledCounter > ledOnTime){
				ledState = LED_OFF;
				ledCounter = 0;
			}
			TurnLedOn();
		break;
		case LED_OFF: //1 --> 0ff
			if(ledCounter > ledOffTime){
				ledState = LED_ON;
				ledCounter = 0;
			}
			TurnLedOff();
		break;
		
		default:
		break;
	}
}



void main(){
	Sys_init();
	Led_Setup(1, 5);
	while(1){
		Led_Operation_Processing();
		HAL_Delay(DELAY_TIME);
	}
}