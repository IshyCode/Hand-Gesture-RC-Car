/* USER CODE BEGIN Header */

/**

  ******************************************************************************

  * @file           : main.h

  * @brief          : Header for main.c file.

  ******************************************************************************

  */

/* USER CODE END Header */

#ifndef __MAIN_H

#define __MAIN_H



#ifdef __cplusplus

extern "C" {

#endif



#include "stm32l4xx_hal.h"



/* Exported functions prototypes ---------------------------------------------*/

void Error_Handler(void);



/* UART handle */

extern UART_HandleTypeDef huart2;

extern uint8_t rxByte;



/* ---------------- MOTOR CONTROL PINS ---------------- */



/* Back Motors */

#define ENA_Pin        GPIO_PIN_0

#define ENA_GPIO_Port  GPIOA

#define IN1_Pin        GPIO_PIN_1

#define IN1_GPIO_Port  GPIOA

#define IN2_Pin        GPIO_PIN_4

#define IN2_GPIO_Port  GPIOA

#define IN3_Pin        GPIO_PIN_5

#define IN3_GPIO_Port  GPIOA

#define IN4_Pin        GPIO_PIN_6

#define IN4_GPIO_Port  GPIOA

#define ENB_Pin        GPIO_PIN_7

#define ENB_GPIO_Port  GPIOA



/* Front Motors */

#define F_ENA_Pin      GPIO_PIN_8

#define F_ENA_GPIO_Port GPIOA

#define F_IN1_Pin      GPIO_PIN_9

#define F_IN1_GPIO_Port GPIOA

#define F_IN2_Pin      GPIO_PIN_10

#define F_IN2_GPIO_Port GPIOA

#define F_ENB_Pin      GPIO_PIN_0

#define F_ENB_GPIO_Port GPIOB

#define F_IN3_Pin      GPIO_PIN_1

#define F_IN3_GPIO_Port GPIOB

#define F_IN4_Pin      GPIO_PIN_2

#define F_IN4_GPIO_Port GPIOB



/* Other pins */

#define B1_Pin GPIO_PIN_13

#define B1_GPIO_Port GPIOC

#define TMS_Pin GPIO_PIN_13

#define TMS_GPIO_Port GPIOA

#define TCK_Pin GPIO_PIN_14

#define TCK_GPIO_Port GPIOA

#define SWO_Pin GPIO_PIN_3

#define SWO_GPIO_Port GPIOB



#ifdef __cplusplus

}

#endif



#endif /* __MAIN_H */
