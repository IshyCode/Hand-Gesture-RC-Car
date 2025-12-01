/* USER CODE BEGIN Header */

/**

  ******************************************************************************

  * @file           : main.c

  * @brief          : Main program body with front/back and left/right motor sync

  ******************************************************************************

  */

/* USER CODE END Header */

#include "main.h"



/* UART handle and RX byte */

UART_HandleTypeDef huart2;

uint8_t rxByte;



/* Function prototypes */

void SystemClock_Config(void);

static void MX_GPIO_Init(void);

static void MX_USART2_UART_Init(void);



/* ---------------- USER MOTOR FUNCTIONS ---------------- */

// Stop all motors

void stopMotors(void) {

    // Disable all motor enables

    HAL_GPIO_WritePin(ENA_GPIO_Port, ENA_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(ENB_GPIO_Port, ENB_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin, GPIO_PIN_RESET);



    // Set all IN pins low

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN1_GPIO_Port, F_IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN2_GPIO_Port, F_IN2_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN3_GPIO_Port, F_IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN4_GPIO_Port, F_IN4_Pin, GPIO_PIN_RESET);

}



// Forward (left and right motors synced)

void forward(void) {

    HAL_GPIO_WritePin(ENA_GPIO_Port, ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(ENB_GPIO_Port, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin, GPIO_PIN_SET);



    // Left motors (front & back)

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN1_GPIO_Port, F_IN1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN2_GPIO_Port, F_IN2_Pin, GPIO_PIN_RESET);



    // Right motors (front & back) inverted

    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN3_GPIO_Port, F_IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN4_GPIO_Port, F_IN4_Pin, GPIO_PIN_SET);

}



void backward(void) {

    HAL_GPIO_WritePin(ENA_GPIO_Port, ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(ENB_GPIO_Port, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin, GPIO_PIN_SET);



    // Left motors

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN1_GPIO_Port, F_IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN2_GPIO_Port, F_IN2_Pin, GPIO_PIN_SET);



    // Right motors inverted

    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN3_GPIO_Port, F_IN3_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN4_GPIO_Port, F_IN4_Pin, GPIO_PIN_RESET);

}





void left(void) {

    // Enable all motors

    HAL_GPIO_WritePin(ENA_GPIO_Port, ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(ENB_GPIO_Port, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin, GPIO_PIN_SET);



    // Left motors backward

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN1_GPIO_Port, F_IN1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN2_GPIO_Port, F_IN2_Pin, GPIO_PIN_SET);



    // Right motors forward

    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN3_GPIO_Port, F_IN3_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN4_GPIO_Port, F_IN4_Pin, GPIO_PIN_RESET);

}



void right(void) {

    // Enable all motors

    HAL_GPIO_WritePin(ENA_GPIO_Port, ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(ENB_GPIO_Port, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin, GPIO_PIN_SET);



    // Left motors forward

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN1_GPIO_Port, F_IN1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN2_GPIO_Port, F_IN2_Pin, GPIO_PIN_RESET);



    // Right motors backward

    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(F_IN3_GPIO_Port, F_IN3_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(F_IN4_GPIO_Port, F_IN4_Pin, GPIO_PIN_SET);

}



/* UART receive interrupt callback */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if(huart->Instance == USART2) {

        switch(rxByte) {

            case 'w': case 'W': forward(); break;

            case 's': case 'S': backward(); break;

            case 'a': case 'A': left(); break;

            case 'd': case 'D': right(); break;

            case 'x': case 'X': stopMotors(); break;

        }

        HAL_UART_Receive_IT(&huart2, &rxByte, 1);

    }

}



/* ---------------- MAIN ---------------- */

int main(void) {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_USART2_UART_Init();



    /* start UART interrupt */

    HAL_UART_Receive_IT(&huart2, &rxByte, 1);



    while(1) {

        /* idle loop */

    }

}



/* ---------------- SYSTEM CONFIG ---------------- */

void SystemClock_Config(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};



    if(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)

        Error_Handler();



    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;

    RCC_OscInitStruct.HSIState = RCC_HSI_ON;

    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    RCC_OscInitStruct.PLL.PLLM = 1;

    RCC_OscInitStruct.PLL.PLLN = 10;

    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;

    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;

    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();



    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|

                                  RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) Error_Handler();

}



/* ---------------- GPIO INIT ---------------- */

static void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};



    /* Clocks */

    __HAL_RCC_GPIOA_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();

    __HAL_RCC_GPIOH_CLK_ENABLE();



    /* Back motor pins */

    HAL_GPIO_WritePin(GPIOA, ENA_Pin|IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin|ENB_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = ENA_Pin|IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin|ENB_Pin;

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

    GPIO_InitStruct.Pull = GPIO_NOPULL;

    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



    /* Front motor pins */

    HAL_GPIO_WritePin(F_ENA_GPIO_Port, F_ENA_Pin|F_IN1_Pin|F_IN2_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = F_ENA_Pin|F_IN1_Pin|F_IN2_Pin;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



    HAL_GPIO_WritePin(F_ENB_GPIO_Port, F_ENB_Pin|F_IN3_Pin|F_IN4_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = F_ENB_Pin|F_IN3_Pin|F_IN4_Pin;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



    /* Button */

    GPIO_InitStruct.Pin = B1_Pin;

    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;

    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

}



/* ---------------- USART2 INIT ---------------- */

static void MX_USART2_UART_Init(void) {

    huart2.Instance = USART2;

    huart2.Init.BaudRate = 9600;

    huart2.Init.WordLength = UART_WORDLENGTH_8B;

    huart2.Init.StopBits = UART_STOPBITS_1;

    huart2.Init.Parity = UART_PARITY_NONE;

    huart2.Init.Mode = UART_MODE_TX_RX;

    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if(HAL_UART_Init(&huart2) != HAL_OK) Error_Handler();

}



/* ---------------- ERROR HANDLER ---------------- */

void Error_Handler(void) {

    __disable_irq();

    while(1) {}

}
