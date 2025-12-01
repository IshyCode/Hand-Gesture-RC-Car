/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
uint8_t rx_byte;

/* USER CODE BEGIN PV */
// Motor control prototypes
void stopMotors(void);
void forward(void);
void backward(void);
void left(void);
void right(void);
/* USER CODE END PV */


/* Function Prototypes -------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);


/* USER CODE BEGIN 0 */

// -------- Motor Control Functions --------
void stopMotors(void)
{
    HAL_GPIO_WritePin(GPIOA, ENA_Pin|ENB_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin, GPIO_PIN_RESET);
}

void forward(void) {
    // Enable both motors
    HAL_GPIO_WritePin(GPIOA, ENA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, ENB_Pin, GPIO_PIN_SET);

    // Motor A forward
    HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_RESET);

    // Motor B forward
    HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_RESET);
}

void backward(void) {
    HAL_GPIO_WritePin(GPIOA, ENA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_SET);
}

void left(void) {
    HAL_GPIO_WritePin(GPIOA, ENA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_RESET);
}

void right(void) {
    HAL_GPIO_WritePin(GPIOA, ENA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, ENB_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, IN2_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOA, IN3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, IN4_Pin, GPIO_PIN_SET);
}




// UART RX interrupt callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        switch (rx_byte)
        {
            case 'F': forward(); break;
            case 'B': backward(); break;
            case 'L': left(); break;
            case 'R': right(); break;
            case 'S': stopMotors(); break;
        }

        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}

/* USER CODE END 0 */


/* MAIN ----------------------------------------------------------------------*/
int main(void)
{
  HAL_Init();

  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  stopMotors();

  HAL_UART_Receive_IT(&huart1, &rx_byte, 1);

  while (1)
  {
      // interrupt driven
  }
}


/* --------------------------------------------------------------------------
   SYSTEM CLOCK CONFIG  (CubeMX generated)
   --------------------------------------------------------------------------*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

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

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    Error_Handler();
}


/* --------------------------------------------------------------------------
   GPIO INIT  (CubeMX generated)
   --------------------------------------------------------------------------*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = ENA_Pin | IN1_Pin | IN2_Pin |
                        IN3_Pin | IN4_Pin | ENB_Pin;

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, ENA_Pin|IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin|ENB_Pin, GPIO_PIN_RESET);
}


/* --------------------------------------------------------------------------
   USART1 INIT  (CubeMX generated)
   --------------------------------------------------------------------------*/
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart1) != HAL_OK)
    Error_Handler();
}


/* ERROR HANDLER -------------------------------------------------------------*/
void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}

