#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "focusButton.h"
#include "main.h"

bool focusSet = false;
bool shootSet = false;

void focusButtonSet (void)
{
	//if (focusSet)
	{
		HAL_GPIO_WritePin (GPIOC, FOCUSBUTTON, GPIO_PIN_SET);
		focusSet = true;
	}
}

void focusButtonReSet (void)
{
	//if (!focusSet)
	{
		HAL_GPIO_WritePin (GPIOC, FOCUSBUTTON, GPIO_PIN_RESET);	
		focusSet = false;
	}
}

bool shootButtonSet (void)
{	
	//if (!shootSet)
	{
		HAL_GPIO_WritePin (GPIOC, SHOOTBUTTON, GPIO_PIN_RESET);
		shootSet = true;
		HAL_Delay (100);
	}
	//if (shootSet)
	{
		HAL_GPIO_WritePin (GPIOC, SHOOTBUTTON, GPIO_PIN_SET);
		shootSet = false;
		return 1;
	}
}