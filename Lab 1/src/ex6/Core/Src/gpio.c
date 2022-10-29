/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
static uint16_t clockPin[ANALOG_CLOCK_NUMBER] =
{
		ONE_HR_Pin,
		TWO_HR_Pin,
		THREE_HR_Pin,
		FOUR_HR_Pin,
		FIVE_HR_Pin,
		SIX_HR_Pin,
		SEVEN_HR_Pin,
		EIGHT_HR_Pin,
		NINE_HR_Pin,
		TEN_HR_Pin,
		ELEVEN_HR_Pin,
		TWELVE_HR_Pin
};

static GPIO_TypeDef * clockPort[ANALOG_CLOCK_NUMBER] =
{
		ONE_HR_GPIO_Port,
		TWO_HR_GPIO_Port,
		THREE_HR_GPIO_Port,
		FOUR_HR_GPIO_Port,
		FIVE_HR_GPIO_Port,
		SIX_HR_GPIO_Port,
		SEVEN_HR_GPIO_Port,
		EIGHT_HR_GPIO_Port,
		NINE_HR_GPIO_Port,
		TEN_HR_GPIO_Port,
		ELEVEN_HR_GPIO_Port,
		TWELVE_HR_GPIO_Port
};
/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ONE_HR_Pin|TWO_HR_Pin|THREE_HR_Pin|FOUR_HR_Pin
                          |FIVE_HR_Pin|SIX_HR_Pin|SEVEN_HR_Pin|EIGHT_HR_Pin
                          |NINE_HR_Pin|TEN_HR_Pin|ELEVEN_HR_Pin|TWELVE_HR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = ONE_HR_Pin|TWO_HR_Pin|THREE_HR_Pin|FOUR_HR_Pin
                          |FIVE_HR_Pin|SIX_HR_Pin|SEVEN_HR_Pin|EIGHT_HR_Pin
                          |NINE_HR_Pin|TEN_HR_Pin|ELEVEN_HR_Pin|TWELVE_HR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void Turn_On_Led(uint8_t pos){
	if (pos < 0 || pos >= ANALOG_CLOCK_NUMBER) return;
	HAL_GPIO_WritePin(clockPort[pos], clockPin[pos], ENABLE);
}
void Turn_Off_Led(uint8_t pos){
	if (pos < 0 || pos >= ANALOG_CLOCK_NUMBER) return;
	HAL_GPIO_WritePin(clockPort[pos], clockPin[pos], DISABLE);
}
void State_Display(uint8_t pos, uint8_t state){
	if (pos < 0 || pos >= ANALOG_CLOCK_NUMBER) return;
	HAL_GPIO_WritePin(clockPort[pos], clockPin[pos], state);
}
void Clock_Display(uint8_t buffer[], uint8_t size){
	for (uint8_t index = 0; index < size; index++){
		HAL_GPIO_WritePin(clockPort[index], clockPin[index], buffer[index]);
	}
}
/* USER CODE END 2 */
