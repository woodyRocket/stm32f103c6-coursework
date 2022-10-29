/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_RED 					PA5
#define LED_YELLOW 					PA6
#define LED_GREEN 					PA7
#define SEG_A						PB0
#define SEG_B						PB1
#define SEG_C						PB2
#define SEG_D						PB3
#define SEG_E						PB4
#define SEG_F						PB5
#define SEG_G						PB6

#define ENABLE 						RESET
#define DISABLE 					SET
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void Turn_On_Red(void);
void Turn_Off_Red(void);
void Turn_On_Yellow(void);
void Turn_Off_Yellow(void);
void Turn_On_Green(void);
void Turn_Off_Green(void);
void Data_Out(GPIO_TypeDef* Port, uint16_t Pin, GPIO_PinState state);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

