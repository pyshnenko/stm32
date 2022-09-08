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

int funcForback = 0;

int forBack (void)
{
	return funcForback;
}

void leftButtonPress (int function)
{
	if (function==2)
	{
		focusButtonSet();
		workedFunction(1);
		return;
	}
	
	if ((function == 1)||(function == 0)||(function == BACKMENU+9)||(function == ENDLESSMODE*10)
						||(function == LIMITEDMODE*10)||(function == ABOUT*10)) //меню из режима one shoot
	{
		if(function!=14)
			funcForback=function;
		clearCentralBox();
		ssd1306_InvertColors();
		centralBoxText("one shoot ", 0, 10);
		ssd1306_InvertColors();
		centralBoxText("endless   ", 1, 10);
		workedFunction(10);
		return;
	}
	
	if (function == 10)										//endless
	{
		ssd1306_InvertColors();
		centralBoxText("endless   ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("one shoot ", 0, 10);
		workedFunction(11);
		return;
	}	
	if (function == 11)										//limited
	{
		ssd1306_InvertColors();
		centralBoxText("limited   ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("endless   ", 0, 10);
		workedFunction(12);
		return;
	}
	if (function == 12)										//wireless
	{
		ssd1306_InvertColors();
		centralBoxText("wireless  ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("limited   ", 0, 10);
		workedFunction(13);
		return;
	}
	if (function == 13)											//about
	{
		ssd1306_InvertColors();
		centralBoxText("about     ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("wireless  ", 0, 10);
		workedFunction(14);
		return;
	}
	if (function == 14)											//back
	{
		ssd1306_InvertColors();
		centralBoxText("back      ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("about     ", 0, 10);
		workedFunction(15);
		return;
	}
	if (function == 21)											//endless no
	{
		workedFunction(20);
		return;
	}
	if (function == 31)											//limited no
	{
		workedFunction(30);
		return;
	}
	if ((function == WIRELESSSET*10)||(function == WIRELESSSET*10+6)||(function == WIRELESSSET*100+1))
	{
		ssd1306_InvertColors();
		centralBoxText("scan      ", 0, 10);
		ssd1306_InvertColors();
		centralBoxText("status    ", 1, 10);
		workedFunction(41);
		return;
	}
	if (function == WIRELESSSET*10+1)
	{
		ssd1306_InvertColors();
		centralBoxText("status    ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("scan      ", 0, 10);
		workedFunction(42);
		return;
	}
	if (function == WIRELESSSET*10+2)
	{
		ssd1306_InvertColors();
		centralBoxText("settings  ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("status    ", 0, 10);
		workedFunction(43);
		return;
	}
	if (function == WIRELESSSET*10+3)
	{
		ssd1306_InvertColors();
		centralBoxText("back      ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("settings  ", 0, 10);
		workedFunction(44);
		return;
	}
	if (function == WIRELESSSET*10+4)
	{
		ssd1306_InvertColors();
		centralBoxText("pult      ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("settings  ", 0, 10);
		workedFunction(45);
		return;
	}
	if (function == WIRELESSSET*10+5)
	{
		ssd1306_InvertColors();
		centralBoxText("back      ", 1, 10);
		ssd1306_InvertColors();
		centralBoxText("pult      ", 0, 10);
		workedFunction(46);
		return;
	}
}