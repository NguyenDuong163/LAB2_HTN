/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SCAN_FREQ 250 // 1s -> 1hz
#define SCAN_TIME 1000/SCAN_FREQ
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void test_LedY0();
void test_LedY1();
void test_7seg();
void traffic_light();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int hour = 10;
int min = 47;
int second = 53;
int num = 0;
int colon = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  led7_SetColon(1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  traffic_light();
	  if (flag_timer3){
		  setTimer3(500);
		  HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
 		  led7_SetColon(colon);
 		  if (colon ==  1){
 			  colon = 0;
 			  led_Off(6);
 		  }
 		  else {
 			  colon = 1;
 			  led_On(6);
 		  }
	  }

	  if (flag_timer_second){
		  setTimerSecond(1000);
		  second = second + 1;
		  if(second >= 60){
			  second = 0;
			  min = min + 1;
			  if (min >= 60){
				  min = 0;
				  hour = (hour +1) % 24;
			  }
		  }
	  }

//	  if (flag_timer7seg){
//		  if (flag_timerS){
//			  setTimerShift(1000);
//			  num ++;
//			  if (num > 3){
//				  num = 0;
//			  }
//		  }
//		  setTimer7seg(2);
//		  test_7seg(num);
//		  led7_Scan();
//	  }

	  if (flag_timer7seg){
		  setTimer7seg(2);
		  settime_7seg();
		  led7_Scan();
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init(){
	  HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
	  HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
	  HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, 0);
	  timer_init();
	  led7_init();
	  setTimer7seg(10);
	  setTimer2(10);
	  setTimer3(10);
	  settime_7seg();
	  setTimerShift(1000);
}

uint8_t count_led_debug = 0;
uint8_t count_led_Y0 = 0;
uint8_t count_led_Y1 = 0;
uint8_t count_traffic	= 0;

void test_LedDebug(){
	count_led_debug = (count_led_debug + 1)%2;
	if(count_led_debug == 0){
		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	}
}

void test_LedY0(){
	count_led_Y0 = (count_led_Y0+ 1)% 6;
	if(count_led_Y0 > 40){
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 1);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
	}
}

void test_LedY1(){
	count_led_Y1 = (count_led_Y1+ 1)% 6;
	if(count_led_Y1 > 10){
		HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y1_Pin, 1);
	}
}

void traffic_light(){
	count_traffic = (count_traffic + 1) % 9;
	if (count_traffic <= 3){
		HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port , OUTPUT_Y1_Pin , 0);
		HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port , DEBUG_LED_Pin , 1);
	}
	if (count_traffic >3 && count_traffic <= 4){
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port , OUTPUT_Y0_Pin , 1);
		HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port , DEBUG_LED_Pin , 0);
	}
	if (count_traffic > 4){
		HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port , OUTPUT_Y1_Pin , 1);
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port , OUTPUT_Y0_Pin , 0);
	}
}

void test_7seg(int num){
	if (num == 0){
		led7_SetDigit(1, 0, 0);
		led7_SetDigit(2, 1, 0);
		led7_SetDigit(3, 2, 0);
		led7_SetDigit(4, 3, 0);
	} else if (num == 1){
		led7_SetDigit(4, 0, 0);
		led7_SetDigit(1, 1, 0);
		led7_SetDigit(2, 2, 0);
		led7_SetDigit(3, 3, 0);
	} else if (num == 2){
		led7_SetDigit(3, 0, 0);
		led7_SetDigit(4, 1, 0);
		led7_SetDigit(1, 2, 0);
		led7_SetDigit(2, 3, 0);
	} else if (num == 3){
		led7_SetDigit(2, 0, 0);
		led7_SetDigit(3, 1, 0);
		led7_SetDigit(4, 2, 0);
		led7_SetDigit(1, 3, 0);
	}
}

void settime_7seg(){
	led7_SetDigit(hour/10, 0, 0);
	led7_SetDigit(hour%10, 1, 0);
	led7_SetDigit(min/10, 2, 0);
	led7_SetDigit(min%10, 3, 0);
}
/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
