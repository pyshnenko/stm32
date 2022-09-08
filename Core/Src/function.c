#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "string.h"
#include "focusButton.h"
#include "function.h"
#include "main.h"
#include "leftButtonPress.h"
#include "rightButtonPress.h"
#include "workedFunction.h"

void setFunction (int function)
{
	if (function==3)
		workedFunction(1);
	if (function==20)
	{
		workedFunction(20);
	}
	if ((function==30)||(function==31))
	{
		workedFunction(30);
	}
}

int checkingNum(int pos, int start)
{
	bool endless=1, left=0, right=0;
	int data[5], posNum=0;
	data[0]=(start/10000)%10;
	data[1]=(start/1000)%10;
	data[2]=(start/100)%10;
	data[3]=(start/10)%10;
	data[4]=start%10;
	while (endless)
	{
		for (int i=0; i<5; i++)
		{
			if (i==posNum)
			{
				ssd1306_InvertColors();
				ssd1306_SetCursor(11*i, 8+(pos*18));
				ssd1306_WriteChar(data[i]+'0', Font_11x18, White);
				ssd1306_InvertColors();
			}
			else {
				ssd1306_SetCursor(11*i, 8+(pos*18));
				ssd1306_WriteChar(data[i]+'0', Font_11x18, White);				
			}
		}
		if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
		{
			ssd1306_InvertColors();
			leftButtonName("up");
			ssd1306_InvertColors();
			left=1;
		}
		if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))
		{
			ssd1306_InvertColors();
			rightButtonName("ok");
			ssd1306_InvertColors();
			right=1;
		}
		if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))&&(left))
		{
			left=0;
			leftButtonName("up");
			data[posNum]++;
			if (data[posNum]>9) data[posNum]=0;
		}
		if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))&&(right))
		{
			right=0;
			rightButtonName("ok");
			posNum++;
			if (posNum>5) 
			{
				int extData=data[4]+data[3]*10+data[2]*100+data[1]*1000+data[0]*10000;
				return extData;
			}
		}
		updateScreen();
	}
	
}

int endlessMode(int pause, int focus, int total)
{
	if (total == 0) total = 65535;
	bool lbut=0;
	int count=0;
	while (count<total)
	{
		if (total<65535) 
		{
			ssd1306_WriteIntOnCentralBox(total-count,0,0);
			updateScreen();
		}
		focusButtonReSet();
		for (int i=0; i<focus; i++)
		{
			if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
			{
				ssd1306_InvertColors();
				leftButtonName("cancel");
				ssd1306_InvertColors();
				updateScreen();
				lbut=1;
			}		
			if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))&&(lbut))
			{
				leftButtonName("cancel");
				updateScreen();
				focusButtonSet();
				return count;
			}
			HAL_Delay(0);
		}
		shootButtonSet();
		focusButtonSet();
		count++;
		photoCounter(count);
		updateScreen();
		for (int i=0; i<pause; i++)
		{
			if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))
			{
				ssd1306_InvertColors();
				leftButtonName("cancel");
				ssd1306_InvertColors();
				updateScreen();
				lbut=1;
			}		
			if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))&&(lbut))
			{
				leftButtonName("cancel");
				updateScreen();
				return count;
			}
			HAL_Delay(0);
		}
	}
	return total;	
}

void hexToAsciiForSend(uint64_t tube, char* id)
{
for (int i=2; i<15; i++)
	{
		uint64_t buf=(tube>>((13-i)*4))&0xF;
		if (buf>=0xA) id[i]=buf+'0'+7;
		else id[i]=buf+'0';
	}
}

void itoa (int num, char* buf)
{
	/*int c=0, numBuf=num;
	if (numBuf == 0)
	{
		buf="0";
		c++;
	}
	else{
		char* buf2;
		while (numBuf>0)
		{
			buf2[c]=(numBuf%10)+'0';
			numBuf/=10;
			c++;
		}
		for (int i=0; i<c; i++)
			buf[i]=buf2[c-i-1];
	}
	buf[c]='\0';
	return;*/
}

void uartSend(char *buf)
{
	int col=strlen(buf);
	uartOffSend(buf, col);
}

void uartSendInt(int buf)
{
	char *sendBuf;
	itoa(buf, sendBuf);
	uartSend(sendBuf);
	uartSend("\r\n");
}