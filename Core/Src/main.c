/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <cstring>
#include "ssd1306.h"
#include "fonts.h"
#include <stdio.h>
#include <stdbool.h>
#include "display.h"
#include "RF24.h"
#include "focusButton.h"
#include "function.h"
#include "main.h"
#include "leftButtonPress.h"
#include "rightButtonPress.h"
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
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

int function=0, photoCol=0, pauseTime=0, focusTime=0, total=0;
char rightButtonText[] = "connect";
char leftButtonText[] = "menu";
bool LCDTrue=0, nrfInit=0, pultConnected=0;

const uint64_t pipe1 = 0xE8E8F0F0E2LL;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void workedFunction (int buffer)
{
	function=buffer;
	if (function == 0)
	{
		uartSend ("camera not connected\r\n");
		strcpy(leftButtonText, "menu");
		strcpy(rightButtonText, "focus");
		clearCentralBox();
		centralBoxText("camera not connected", 0, 20);
		ssd1306_UpdateScreen(&hi2c1);
	}
	if (function == 1)
	{
		uartSend ("one shoot mode\r\n");
		strcpy(leftButtonText, "menu");
		strcpy(rightButtonText, "focus");
		clearCentralBox();
		centralBoxText("one shoot mode", 0, 14);
		setFunction(1);
		ssd1306_UpdateScreen(&hi2c1);
	}
	if (function == 2)
	{
		uartSend ("focus\r\n");
		strcpy(leftButtonText, "cancel");
		strcpy(rightButtonText, "shoot");
		centralBoxText("focus", 1, 5);
		setFunction(2);
		ssd1306_UpdateScreen(&hi2c1);
	}
	if (function == 3)
	{
		uartSend ("photo\r\n");
		photoCol++;
		photoCounter(photoCol);		
		char local[20];
		sprintf (local, "total photos: %d\r\n", photoCol);
		uartSend (local);
		uartSendInt (photoCol);
		shootButtonIcon(0);
		ssd1306_UpdateScreen(&hi2c1);
		setFunction(3);
	}
	if (function == 10)
	{
		scrollBar(6,0);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		uartSend ("menu opened\r\n1. one shoot\r\n2. endless\r\n");
		uartSend ("3. limited\r\n4. wireless\r\n5. about\r\n6. back\r\n");
		ssd1306_UpdateScreen(&hi2c1);		
	}
	if (function == 11)
	{
		scrollBar(6,1);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	if (function == 12)
	{
		scrollBar(6,2);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	if (function == 13)
	{
		scrollBar(6,3);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	if (function == 14)
	{
		scrollBar(6,4);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	if (function == 15)
	{
		scrollBar(6,5);
		strcpy(leftButtonText, "down");
		strcpy(rightButtonText, "ok");
		leftButtonName(leftButtonText);
		rightButtonName(rightButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	
	
	if (function == 20)													//endless start
	{
		scrollBar(1,0);
		photoCounter(photoCol);
		strcpy(leftButtonText, "menu");
		leftButtonName(leftButtonText);
		strcpy(rightButtonText, "settings");
		rightButtonName(rightButtonText);
		clearCentralBox();
		centralBoxText("endless", 0, 7);
		centralBoxText("mode", 1, 4);
		ssd1306_UpdateScreen(&hi2c1);	
		strcpy(leftButtonText, "menu");	
	}	
	
	if (function == 21)													//endless start
	{
		scrollBar(1,0);
		strcpy(leftButtonText, "up");
		leftButtonName(leftButtonText);
		strcpy(rightButtonText, "ok");
		rightButtonName(rightButtonText);
		centralBoxText("pause time", 0, 10);
		pauseTime=checkingNum(1, 1000);
		centralBoxText("focus time", 0, 10);
		focusTime=checkingNum(1, 500);
		clearCentralBox();
		centralBoxText("start?", 0, 6);
		strcpy(leftButtonText, "no");
		strcpy(rightButtonText, "yes");
		rightButtonName(rightButtonText);
		leftButtonName(leftButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
	}
	
	if (function == 22)
	{
		strcpy(leftButtonText, "cancel");
		leftButtonName(leftButtonText);	
		strcpy(rightButtonText, "  ");
		rightButtonName(rightButtonText);	
		char buf[11]="pause    0\0";
		int set=pauseTime, i=0;
		while (set>0)
		{
			buf[9-i]=set%10+'0';
			set/=10;
			i++;
		}
		centralBoxText(buf, 0, 10);
		char buf1[11]="focus    0\0";
		set=focusTime;
		i=0;
		while (set>0)
		{
			buf1[9-i]=set%10+'0';
			set/=10;
			i++;
		}
		centralBoxText(buf1, 1, 10);
		ssd1306_UpdateScreen(&hi2c1);	
		photoCol+=endlessMode(pauseTime, focusTime, 0);
		setFunction(20);
	}
	if (function == 30)													//limited start
	{
		scrollBar(3,0);
		strcpy(leftButtonText, "menu");
		leftButtonName(leftButtonText);
		strcpy(rightButtonText, "settings");
		rightButtonName(rightButtonText);
		clearCentralBox();
		centralBoxText("limited", 0, 7);
		centralBoxText("mode", 1, 4);
		ssd1306_UpdateScreen(&hi2c1);	
		strcpy(leftButtonText, "menu");	
	}		
	if (function == 31)													//limited start
	{
		scrollBar(1,0);
		strcpy(leftButtonText, "up");
		leftButtonName(leftButtonText);
		strcpy(rightButtonText, "ok");
		rightButtonName(rightButtonText);
		scrollBar(3,0);
		centralBoxText("pause time", 0, 10);
		pauseTime=checkingNum(1, 1000);
		scrollBar(3,1);
		centralBoxText("focus time", 0, 10);
		focusTime=checkingNum(1, 500);
		scrollBar(3,2);
		clearCentralBox();
		centralBoxText("total", 0, 5);
		total=checkingNum(1, 0);
		clearCentralBox();
		centralBoxText("start?", 0, 6);
		strcpy(leftButtonText, "no");
		strcpy(rightButtonText, "yes");
		rightButtonName(rightButtonText);
		leftButtonName(leftButtonText);
		ssd1306_UpdateScreen(&hi2c1);		
		if (total==0) setFunction(31);
	}
		if (function == 32)
	{
		strcpy(leftButtonText, "cancel");
		leftButtonName(leftButtonText);	
		strcpy(rightButtonText, "  ");
		rightButtonName(rightButtonText);	
		clearCentralBox();
		ssd1306_UpdateScreen(&hi2c1);	
		photoCol+=endlessMode(pauseTime, focusTime, total);
		setFunction(30);
	}
	if (function == 40)													//wireles start
	{
		strcpy(leftButtonText, "down");
		leftButtonName(leftButtonText);
		strcpy(rightButtonText, "ok");
		rightButtonName(rightButtonText);
		clearCentralBox();
		leftButtonPress(function);
		strcpy(leftButtonText, "down");	
		return;		
	}		
	if (function == 41)
	{
		scrollBar(4+pultConnected,0);
		ssd1306_UpdateScreen(&hi2c1);	
		return;				
	}		
	if (function == 42)
	{
		scrollBar(4+pultConnected,1);
		ssd1306_UpdateScreen(&hi2c1);	
		return;		
	}	
	if (function == 43)
	{
		if (pultConnected) function = 44;
		scrollBar(4+pultConnected,2);
		ssd1306_UpdateScreen(&hi2c1);	
		return;				
	}	
	if (function == 44)
	{
		function=46;
		scrollBar(4+pultConnected,2);
		ssd1306_UpdateScreen(&hi2c1);	
		return;				
	}	
	if (function == 45)
	{
		scrollBar(4+pultConnected,3);
		ssd1306_UpdateScreen(&hi2c1);	
		return;				
	}	
	if (function == 46)
	{
		scrollBar(4+pultConnected,3+pultConnected);
		ssd1306_UpdateScreen(&hi2c1);	
		return;				
	}	
	if (function == 50)
	{
		scrollBar(1,0);
		strcpy(rightButtonText, "  ");
		rightButtonName(rightButtonText);
		strcpy(leftButtonText, "menu");
		leftButtonName(leftButtonText);	
		clearCentralBox();
		ssd1306_SetCursor(0,9);
		ssd1306_WriteString("tube adres:", Font_7x10, White);
		ssd1306_SetCursor(0,19);
		char id[15]="0x000000000000";
		hexToAsciiForSend(pipe1, id);
		ssd1306_WriteString(id, Font_7x10, White);
		ssd1306_SetCursor(0,29);
		if (nrfInit) ssd1306_WriteString("NRF24 OK", Font_7x10, White);
		else ssd1306_WriteString("NRF24 NOT OK", Font_7x10, White);
		ssd1306_SetCursor(0,39);
		if (checkPhoto()) ssd1306_WriteString("PHOTO OK", Font_7x10, White);
		else ssd1306_WriteString("PHOTO NOT OK", Font_7x10, White);
		ssd1306_UpdateScreen(&hi2c1);	
	}
	if (function == WIRELESSSET*100+1)
	{
		strcpy(rightButtonText, "start");
		rightButtonName(rightButtonText);
		strcpy(leftButtonText, "back");
		leftButtonName(leftButtonText);			
		ssd1306_UpdateScreen(&hi2c1);	
	}
}


void uartOffSend (uint8_t *buf, int col)
{
	HAL_UART_Transmit(&huart1, buf, col, 0xFFFF);	
}

void updateScreen(void)
{
		ssd1306_UpdateScreen(&hi2c1);			
}
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart1, "Hello world\r\n", 13, 0xFFFF);
	int setter = ssd1306_Init(&hi2c1);
	bool photoStat=0;
	if (setter == 0) {
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart1, "Sucsessfull\r\n", 13, 0xFFFF);
		ssd1306_Fill(Black);
		ssd1306_UpdateScreen(&hi2c1);

		/*HAL_Delay(1000);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Hello world", Font_11x18, White);
		ssd1306_SetCursor(0, 36);
		ssd1306_WriteString("toxa", Font_11x18, White);  
*/
		// Draw rectangle on screen
		/*for (uint8_t i=0; i<28; i++) {
      for (uint8_t j=0; j<64; j++) {
          ssd1306_DrawPixel(100+i, 0+j, White);
      }
		}*/

		// Copy all data from local screenbuffer to the screen
		
		//ssd1306_UpdateScreen(&hi2c1);
		ssd1306_Clear();
		ssd1306_UpdateScreen(&hi2c1);	
		startPage();
		ssd1306_UpdateScreen(&hi2c1);
		HAL_Delay(500);
		ssd1306_Clear();
		startTable();
		ssd1306_UpdateScreen(&hi2c1);	
		if (checkPhoto())			
		{
			ssd1306_SetCursor(0, 9);
			ssd1306_WriteString("true", Font_11x18, White); 
			photoStat = 1;		
		}
		else{
			ssd1306_SetCursor(0, 9);
			ssd1306_WriteString("false", Font_11x18, White);
		}
		
		//инициализация и проверка nrf24
		
		DWT_Init(); // счётчик для микросекундных пауз


		uint8_t res = isChipConnected(); // проверяет подключён ли модуль к SPI

		char str[64] = {0,};
		snprintf(str, 64, "Connected: %s\n", 1 ? "OK" : "NOT OK");
		ssd1306_SetCursor(0, 9);
		ssd1306_WriteString(str, Font_7x10, White);  
		//HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 1000);

		res = NRF_Init(); // инициализация

		snprintf(str, 64, "Init: %s\n", res > 0 && res < 255 ? "OK" : "NOT OK");
		//HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 1000);		
		ssd1306_SetCursor(0, 19);
		ssd1306_WriteString(str, Font_7x10, White);
		
		if (res > 0 && res < 255) 
		{
			nrfState(true);
			nrfInit=1;
		}
		else nrfState(false);
		ssd1306_UpdateScreen(&hi2c1);	
		HAL_Delay(500);
		LCDTrue=1;
	}
	else {
		
		HAL_UART_Transmit(&huart1, "Fail!!!\r\n", 9, 0xFFFF);
	}
	
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	clearCentralBox();	
	if (photoStat == 0)
	{
		centralBoxText("camera not connected", 0, 20);
		rightButtonName(rightButtonText);
	}
	else{
		workedFunction(1);
	}
	photoCounter(0);
	ssd1306_UpdateScreen(&hi2c1);	
	bool press=0, pressL=0;
  while (1)
  {
		if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			ssd1306_InvertColors();
			rightButtonName(rightButtonText);
			ssd1306_UpdateScreen(&hi2c1);
			ssd1306_InvertColors();
			press=1;
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			rightButtonName(rightButtonText);
			ssd1306_UpdateScreen(&hi2c1);
			if (press)
			{
				press=0;
				rightButtonPress(function);				
			}
		}
		if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			ssd1306_InvertColors();
			leftButtonName(leftButtonText);
			ssd1306_UpdateScreen(&hi2c1);
			ssd1306_InvertColors();
			pressL=1;
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			leftButtonName(leftButtonText);
			ssd1306_UpdateScreen(&hi2c1);
			if (pressL)
			{
				pressL=0;
				leftButtonPress(function);				
			}
		}
		photoStat = checkPhoto();
		ssd1306_UpdateScreen(&hi2c1);
		if (!press || !pressL) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
		else HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
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
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
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
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

