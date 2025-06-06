/**
 * @file periph_init.c
 * @author Marwen BENISMAIL (mbenismail52@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "periph_init.h"
#include "mcu_interface.h"
#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
uint8_t SystemClock_Config(void);
static void MX_GPIO_Init(void);
static uint8_t MX_USART2_UART_Init(void);
static uint8_t MX_USART1_UART_Init(void);

 /**
  * @brief this function is used to initialize the peripherals dedicated to used mcu
  * 
  * @return uint8_t 
  */

 uint8_t periph_init(void)
{
	 uint8_t ret_val;
	 /* MCU Configuration--------------------------------------------------------*/

	  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	 ret_val=HAL_Init();

	  /* USER CODE BEGIN Init */

	  /* USER CODE END Init */

	  /* Configure the system clock */
	 ret_val=SystemClock_Config();

	  /* USER CODE BEGIN SysInit */

	  /* USER CODE END SysInit */

	  /* Initialize all configured peripherals */
	 MX_GPIO_Init();
	 ret_val=MX_USART2_UART_Init();
	 ret_val=MX_USART1_UART_Init();
    return ret_val;
}



 /**
   * @brief System Clock Configuration
   * @retval None
   */
 uint8_t SystemClock_Config(void)
 {
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

   /** Configure the main internal regulator output voltage
   */
   __HAL_RCC_PWR_CLK_ENABLE();
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

   /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLM = 8;
   RCC_OscInitStruct.PLL.PLLN = 72;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ = 3;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
     return 1;
   }

   /** Initializes the CPU, AHB and APB buses clocks
   */
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
   {
     return 1;
   }
   return 0;
 }

 /**
   * @brief USART1 Initialization Function
   * @param None
   * @retval None
   */
 static uint8_t MX_USART1_UART_Init(void)
 {

   /* USER CODE BEGIN USART1_Init 0 */

   /* USER CODE END USART1_Init 0 */

   /* USER CODE BEGIN USART1_Init 1 */

   /* USER CODE END USART1_Init 1 */
   huart1.Instance = USART1;
   huart1.Init.BaudRate = 115200;
   huart1.Init.WordLength = UART_WORDLENGTH_8B;
   huart1.Init.StopBits = UART_STOPBITS_1;
   huart1.Init.Parity = UART_PARITY_NONE;
   huart1.Init.Mode = UART_MODE_TX_RX;
   huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   huart1.Init.OverSampling = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&huart1) != HAL_OK)
   {
	   return 1;
	}
	   return 0;
   /* USER CODE BEGIN USART1_Init 2 */

   /* USER CODE END USART1_Init 2 */

 }

 /**
   * @brief USART2 Initialization Function
   * @param None
   * @retval None
   */
 static uint8_t MX_USART2_UART_Init(void)
 {

   /* USER CODE BEGIN USART2_Init 0 */

   /* USER CODE END USART2_Init 0 */

   /* USER CODE BEGIN USART2_Init 1 */

   /* USER CODE END USART2_Init 1 */
   huart2.Instance = USART2;
   huart2.Init.BaudRate = 115200;
   huart2.Init.WordLength = UART_WORDLENGTH_8B;
   huart2.Init.StopBits = UART_STOPBITS_1;
   huart2.Init.Parity = UART_PARITY_NONE;
   huart2.Init.Mode = UART_MODE_TX_RX;
   huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   huart2.Init.OverSampling = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&huart2) != HAL_OK)
   {
	   return 1;
	}
	   return 0;
   /* USER CODE BEGIN USART2_Init 2 */

   /* USER CODE END USART2_Init 2 */

 }

 /**
   * @brief GPIO Initialization Function
   * @param None
   * @retval None
   */
 static void MX_GPIO_Init(void)
 {
   GPIO_InitTypeDef GPIO_InitStruct = {0};
 /* USER CODE BEGIN MX_GPIO_Init_1 */
 /* USER CODE END MX_GPIO_Init_1 */

   /* GPIO Ports Clock Enable */
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

   /*Configure GPIO pins : PG13 PG14 */
   GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

 /* USER CODE BEGIN MX_GPIO_Init_2 */
 /* USER CODE END MX_GPIO_Init_2 */
 }

 /* USER CODE BEGIN 4 */

 /* USER CODE END 4 */

 /**
   * @brief  Period elapsed callback in non blocking mode
   * @note   This function is called  when TIM2 interrupt took place, inside
   * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
   * a global variable "uwTick" used as application time base.
   * @param  htim : TIM handle
   * @retval None
   */
 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
   /* USER CODE BEGIN Callback 0 */

   /* USER CODE END Callback 0 */
   if (htim->Instance == TIM2) {
     HAL_IncTick();
   }
   /* USER CODE BEGIN Callback 1 */

   /* USER CODE END Callback 1 */
 }

 /**
   * @brief  This function is executed in case of error occurrence.
   * @retval None
   */
 void Error_Handler(void)
 {
   /* USER CODE BEGIN Error_Handler_Debug */
   /* User can add his own implementation to report the HAL error return state */
   __disable_irq();
   while (1)
   {
   }
   /* USER CODE END Error_Handler_Debug */
 }
