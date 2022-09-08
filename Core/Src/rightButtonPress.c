#include "leftButtonPress.h"
#include "rightButtonPress.h"
#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "string.h"
#include "focusButton.h"
#include "function.h"
#include "main.h"
#include "workedFunction.h"

int funcForbackL = 0;

void rightButtonPress (int function)
{
	if (function == 0)	//функция принудительного подключения камеры
		workedFunction(1);
	if (function == 1) //функция фокусировки в режиме one shoot
	{
		focusButtonReSet();
		focusButtonIcon(1);
		shootButtonIcon(0);
		workedFunction(2);
		return;
	}
	if (function==2)	//снимок в режиме one shoot
	{
		shootButtonSet();
		shootButtonIcon(1);
		focusButtonSet();
		focusButtonIcon(0);
		workedFunction(3);
		return;
	}
	if (function == 10)
	{
		clearCentralBox();
		workedFunction(1);
		return;
	}
	if (function == 11)					//endless
	{
		clearCentralBox();
		workedFunction(ENDLESSMODE*10);
		return;
	}
	if (function == 12)					//limited
	{
		clearCentralBox();
		workedFunction(LIMITEDMODE*10);
		return;
	}
	if (function == 13)
	{
		clearCentralBox();
		workedFunction(WIRELESSSET*10);
		return;
	}
	if (function == 14)
	{
		clearCentralBox();
		workedFunction(ABOUT*10);
		return;
	}
		
	if (function == 15)
	{
		clearCentralBox();
		workedFunction(forBack());
		return;
	}		
	
	if (function == 20)
	{
		clearCentralBox();
		workedFunction(21);
		return;
	}
	if (function == 21)									//endless start
	{
		leftButtonName("cancel");
		clearCentralBox();
		workedFunction(22);
		return;
	}
	if (function == 30)
	{
		clearCentralBox();
		workedFunction(31);
		return;
	}
		if (function == 31)									//limited start
	{
		leftButtonName("cancel");
		clearCentralBox();
		workedFunction(32);
		return;
	}
	if (function == WIRELESSSET*10+1)
	{
		clearCentralBox();
		centralBoxText("scan  make", 0, 10);
		centralBoxText("find:", 1, 5);
		workedFunction(WIRELESSSET*100+1);
	}
	if (function == 46)
	{
		function=1;
		leftButtonPress(function);
		return;
	}
}