/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"





/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include <stdio.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


char msg[32];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */





void delay_us(uint16_t us);
void Set_DHT11_Pin_Output(void);
void Set_DHT11_Pin_Input(void);
void DHT11_Start(void);
uint8_t DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);

uint16_t Read_ADC_Channel(uint32_t channel);
void Buzzer_On(void);
void Buzzer_Off(void);




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */





  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim2);

  ssd1306_Init();
  ssd1306_Fill(Black);
  ssd1306_SetCursor(10, 10);
  ssd1306_WriteString("MSPA-4 PROJECT", Font_7x10, White);
  ssd1306_SetCursor(20, 30);
  ssd1306_WriteString("Starting...", Font_7x10, White);
  ssd1306_UpdateScreen();
  HAL_Delay(1000);






  /* USER CODE END 2 */



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      static uint32_t lastDhtRead = 0;

      /* Read DHT11 only every 1500 ms */
      if (HAL_GetTick() - lastDhtRead >= 1500)
      {
          lastDhtRead = HAL_GetTick();

          DHT11_Start();
          if (DHT11_CheckResponse())
          {
              Rh_byte1   = DHT11_ReadByte();
              Rh_byte2   = DHT11_ReadByte();
              Temp_byte1 = DHT11_ReadByte();
              Temp_byte2 = DHT11_ReadByte();
              SUM        = DHT11_ReadByte();

              CHECK = Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2;

              if (CHECK == SUM)
              {
                  humidity = (float)Rh_byte1;
                  temperature = (float)Temp_byte1;
              }
          }
      }

      /* Fast sensors: update every loop */
      ldrValue   = Read_ADC_Channel(ADC_CHANNEL_0);   // PA0 = LDR
      heartValue = Read_ADC_Channel(ADC_CHANNEL_4);   // PA4 = Heartbeat

      soundState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);   // PA2 = Sound
      tiltState  = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);   // PA3 = Tilt

      /* Alert logic */
      alert = 0;

      if (temperature > 35.0f)
          alert = 1;

      if (soundState == GPIO_PIN_RESET)
          alert = 1;

      if (tiltState == GPIO_PIN_RESET)
          alert = 1;

      if (ldrValue < 300 || ldrValue > 3500)
          alert = 1;

      if (heartValue > 3000)
          alert = 1;

      if (alert)
          Buzzer_On();
      else
          Buzzer_Off();

      /* OLED display */
      ssd1306_Fill(Black);

      sprintf(msg, "T:%.0fC H:%.0f%%", temperature, humidity);
      ssd1306_SetCursor(0, 0);
      ssd1306_WriteString(msg, Font_7x10, White);

      sprintf(msg, "LDR:%4d", ldrValue);
      ssd1306_SetCursor(0, 12);
      ssd1306_WriteString(msg, Font_7x10, White);

      sprintf(msg, "SND:%s", (soundState == GPIO_PIN_RESET) ? "DET" : "OK");
      ssd1306_SetCursor(0, 24);
      ssd1306_WriteString(msg, Font_7x10, White);

      sprintf(msg, "TILT:%s", (tiltState == GPIO_PIN_RESET) ? "YES" : "NO");
      ssd1306_SetCursor(0, 36);
      ssd1306_WriteString(msg, Font_7x10, White);

      sprintf(msg, "HB:%4d", heartValue);
      ssd1306_SetCursor(0, 48);
      ssd1306_WriteString(msg, Font_7x10, White);

      ssd1306_UpdateScreen();

      HAL_Delay(100);   // fast refresh
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */





uint16_t Read_ADC_Channel(uint32_t channel)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  sConfig.Channel = channel;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  uint16_t value = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);

  return value;
}

void Buzzer_On(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}

void Buzzer_Off(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void delay_us(uint16_t us)
{
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

void Set_DHT11_Pin_Output(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Set_DHT11_Pin_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DHT11_Start(void)
{
  Set_DHT11_Pin_Output();
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_Delay(18);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  delay_us(30);
  Set_DHT11_Pin_Input();
}

uint8_t DHT11_CheckResponse(void)
{
  uint8_t Response = 0;
  delay_us(40);

  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
  {
    delay_us(80);
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
      Response = 1;
  }

  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET);
  return Response;
}

uint8_t DHT11_ReadByte(void)
{
  uint8_t i, j = 0;

  for (i = 0; i < 8; i++)
  {
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET);
    delay_us(40);

    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
      j &= ~(1 << (7 - i));
    }
    else
    {
      j |= (1 << (7 - i));
      while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET);
    }
  }
  return j;
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
