/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENA_Pin GPIO_PIN_0
#define ENA_GPIO_Port GPIOA

#define IN1_Pin GPIO_PIN_1
#define IN1_GPIO_Port GPIOA

#define IN2_Pin GPIO_PIN_2
#define IN2_GPIO_Port GPIOA

#define IN3_Pin GPIO_PIN_3
#define IN3_GPIO_Port GPIOA

#define IN4_Pin GPIO_PIN_4
#define IN4_GPIO_Port GPIOA

#define ENB_Pin GPIO_PIN_5
#define ENB_GPIO_Port GPIOA

extern UART_HandleTypeDef huart1;


/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
