#include <stdint.h>

#define LED_RED PA5
#define LED_YELLOW PA6

/**********************/
/*System init*/
const static uint32_t interruptTime = 10;
const static uint32_t millisecondConversion = 1000;
static uint32_t allLedOffCounter;
static uint32_t singleLedOnCounter, singleLedOffCounter;
/*********************/

enum LED
{
    RED,
    YELLOW,
    OFF
};

enum LED status = RED;

void Turn_On_Red(void)
{
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
}

void Turn_Off_Red(void)
{
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
}

void Turn_On_Yellow(void)
{
    HAL_GPIO_WritePin(LED_YELLOW, LED_YELLOW, RESET);
}

void Turn_Off_Yellow(void)
{
    HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
}

void Turn_Off_All(void)
{
    HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
}

void LED_Setup(uint32_t onTime, uint32_t offTime)
{
    if (interruptTime > 0)
    {
        singleLedOnCounter = onTime * millisecondConversion / interruptTime;
        singleLedOffCounter = offTime * millisecondConversion / interruptTime;
    }
}

void All_Led_Off_Setup(uint32_t offTime)
{
    allLedOffCounter = offTime * millisecondConversion / interruptTime;
}

void LED_Alternating(void)
{
    static uint32_t dynamicRedCounter = 0;
    static uint32_t dynamicYellowCounter = 0;
    static uint32_t dynamicOffCounter = 0;
    switch (status)
    {
    case RED:
        if (dynamicRedCounter <= singleLedOnCounter)
        {
            status = RED;
            dynamicRedCounter++;
            Turn_On_Red();
        }
        else
        {
            status = YELLOW;
            dynamicRedCounter = 0;
            Turn_Off_Red();
        }
        break;
    case YELLOW:
        if (dynamicYellowCounter <= singleLedOffCounter)
        {
            status = YELLOW;
            dynamicYellowCounter++;
            Turn_On_Yellow();
        }
        else
        {
            status = OFF;
            dynamicYellowCounter = 0;
            Turn_Off_Yellow();
        }
        break;
    default:
        if (allLedOffCounter <= 0 || dynamicOffCounter > allLedOffCounter)
        {
            status = RED;
            dynamicOffCounter = 0;
            break;
        }
        else
        {
            status = OFF;
            dynamicOffCounter++;
            Turn_Off_All();
        }
        break;
    }
}

void Interrupt_Service_Routine(void)
{
    LED_Alternating();
}

int main
{
    LED_Setup(2, 2);
    All_Led_Off_Setup(0);
    while (1)
    {
    }
}