#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "string.h"
#include "main.h"

void startTable (void)
{
	for (int i=0; i<128; i++)
		ssd1306_DrawPixel(i, 8, White);
	for (int i=0; i<128; i++)
		ssd1306_DrawPixel(i, 55, White);
	for (int i=0; i<8; i++)
		ssd1306_DrawPixel(64, 63-i, White);
	for (int i=9; i<55; i++)
		ssd1306_DrawPixel(123, i, White);
	ssd1306_SetCursor(0, 56);
	ssd1306_WriteString("menu", Font_7x7, White);
	scrollBar(1,0);
	focusButtonIcon(0);
	shootButtonIcon(0);
}

bool checkPhoto (void)
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
	{
		ssd1306_SetCursor(0, 9);
		draw(0,0, 0x3C00);
		draw(0,1, 0x2400);
		draw(0,2, 0xFE00);
		draw(0,3, 0x8E00);
		draw(0,4, 0xAE00);
		draw(0,5, 0x8E00);
		draw(0,6, 0xFE00);
		return 1;
	}
	draw(0,0, 0x8200);
	draw(0,1, 0x4400);
	draw(0,2, 0x2800);
	draw(0,3, 0x1000);
	draw(0,4, 0x2800);
	draw(0,5, 0x4400);
	draw(0,6, 0x8200);
	return 0;
}

void draw(int xs, int ys, int line)
{
	for (int c=0; c<16; c++)
	{
		if ((0x8000 & line)!=0)
			ssd1306_DrawPixel(xs+c, ys, White);
		else 
			ssd1306_DrawPixel(xs+c, ys, Black);
		line=(line<<1);
	}
}

void scrollBar(int total, int position)
{
	if (total<3)
	{
		for (int i=12; i<53; i++)
		{
			ssd1306_DrawPixel(126, i, White);
			ssd1306_DrawPixel(127, i, White);
			ssd1306_DrawPixel(125, i, White);
		}
		ssd1306_DrawPixel(126, 11, White);
		ssd1306_DrawPixel(126, 53, White);
	}
	else {
		for (int i=11; i<54; i++)
			for (int j=125; j<128; j++)
				ssd1306_DrawPixel(j, i, Black);
		int longs;
		if (total>=40) longs = 1;
		else longs = (40/total);
		int startPosition = 12+(position*longs);
		
		for (int i=startPosition; i<(startPosition+longs+1); i++)
		{
			ssd1306_DrawPixel(126, i, White);
			ssd1306_DrawPixel(127, i, White);
			ssd1306_DrawPixel(125, i, White);
		}
		ssd1306_DrawPixel(126, startPosition-1, White);
		ssd1306_DrawPixel(126, (startPosition+longs+1), White);
	}
}

void nrfState(bool status)
{
	for (int i=118; i<128; i++)
		for (int j=0; j<8; j++)
			ssd1306_DrawPixel(i, j, Black);
	if (status)
	{
		draw(118,2, 0x3E00);
		draw(118,3, 0x4100);
		draw(118,4, 0x9C80);
		draw(118,5, 0x2200);
		draw(118,6, 0x0800);
	}
	else
	{
		ssd1306_DrawPixel (122, 6, White);
	}
}

void startPage (void)
{
		int j=32;
		for (int i=23;i<=41; i++)
			ssd1306_DrawPixel(0, i, White);
		for (int i=20;i<=44; i++)
			ssd1306_DrawPixel(1, i, White);
		for (int i=18;i<=46; i++)
			ssd1306_DrawPixel(2, i, White);
		for (int i=17;i<=47; i++){
			ssd1306_DrawPixel(3, i, White);
			ssd1306_DrawPixel(4, i, White);}
		for (int i=16;i<=48; i++)
			ssd1306_DrawPixel(5, i, White);
		for (int i=15;i<=49; i++){
			ssd1306_DrawPixel(6, i, White);
			ssd1306_DrawPixel(7, i, White);}
		for (int i=14;i<=50; i++){
			ssd1306_DrawPixel(8, i, White);
			ssd1306_DrawPixel(9, i, White);
			ssd1306_DrawPixel(10, i, White);}
		for (int i=13;i<=51; i++)
			for (int ii=11;ii<=17; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=14;i<=50; i++)
			for (int ii=18;ii<=20; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=15;i<=49; i++)
			for (int ii=21;ii<=22; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=16;i<=48; i++)
			for (int ii=23;ii<=24; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=17;i<=47; i++)
				ssd1306_DrawPixel(25, i, White);
		for (int i=18;i<=46; i++)
				ssd1306_DrawPixel(26, i, White);
		for (int i=19;i<=45; i++)
				ssd1306_DrawPixel(27, i, White);
		for (int i=20;i<=44; i++)
				ssd1306_DrawPixel(28, i, White);
		for (int i=21;i<=43; i++)
			for (int ii=29;ii<=95; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=11;i<=53; i++)
				ssd1306_DrawPixel(96, i, White);
		for (int i=10;i<=54; i++)
				ssd1306_DrawPixel(97, i, White);
		for (int i=8;i<=56; i++){
				ssd1306_DrawPixel(98, i, White);
				ssd1306_DrawPixel(99, i, White);}
		for (int i=7;i<=57; i++){
				ssd1306_DrawPixel(100, i, White);
				ssd1306_DrawPixel(101, i, White);}
		for (int i=6;i<=58; i++){
				ssd1306_DrawPixel(102, i, White);
				ssd1306_DrawPixel(103, i, White);}
		for (int i=5;i<=59; i++)
				ssd1306_DrawPixel(104, i, White);
		for (int i=4;i<=60; i++)
			for (int ii=105;ii<=109; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=3;i<=61; i++)
			for (int ii=110;ii<=119; ii++)
				ssd1306_DrawPixel(ii, i, White);
		for (int i=4;i<=60; i++){
				ssd1306_DrawPixel(120, i, White);
				ssd1306_DrawPixel(121, i, White);}
		for (int i=5;i<=59; i++)
				ssd1306_DrawPixel(122, i, White);
		for (int i=6;i<=58; i++)
				ssd1306_DrawPixel(123, i, White);
		for (int i=7;i<=57; i++){
				ssd1306_DrawPixel(124, i, White);
				ssd1306_DrawPixel(125, i, White);}
		for (int i=10;i<=54; i++)
				ssd1306_DrawPixel(126, i, White);
		for (int i=12;i<=52; i++)
				ssd1306_DrawPixel(127, i, White);
		ssd1306_InvertColors();
		ssd1306_DrawPixel(29, 43, White);
		ssd1306_DrawPixel(29, 42, White);
		ssd1306_DrawPixel(29, 41, White);
		ssd1306_DrawPixel(30, 41, White);
		ssd1306_DrawPixel(31, 40, White);
		ssd1306_DrawPixel(31, 39, White);
		ssd1306_DrawPixel(31, 38, White);
		ssd1306_DrawPixel(32, 38, White);
		ssd1306_DrawPixel(32, 37, White);
		ssd1306_DrawPixel(32, 36, White);
		ssd1306_DrawPixel(32, 35, White);
		ssd1306_DrawPixel(33, 35, White);
		ssd1306_DrawPixel(33, 34, White);
		ssd1306_DrawPixel(33, 33, White);
		ssd1306_DrawPixel(33, 32, White);
				
		ssd1306_DrawPixel(29, 21, White);
		ssd1306_DrawPixel(29, 22, White);
		ssd1306_DrawPixel(29, 23, White);
		ssd1306_DrawPixel(30, 23, White);
		ssd1306_DrawPixel(31, 24, White);
		ssd1306_DrawPixel(31, 25, White);
		ssd1306_DrawPixel(31, 26, White);
		ssd1306_DrawPixel(32, 26, White);
		ssd1306_DrawPixel(32, 27, White);
		ssd1306_DrawPixel(32, 28, White);
		ssd1306_DrawPixel(32, 29, White);
		ssd1306_DrawPixel(33, 30, White);
		ssd1306_DrawPixel(33, 30, White);
		ssd1306_DrawPixel(33, 31, White);
		ssd1306_DrawPixel(33, 32, White);
		
		for (int i=96;i<=127;i++){
			ssd1306_DrawPixel(i, 43, White);
			ssd1306_DrawPixel(i, 21, White);
		}
	
		
		ssd1306_InvertColors();
}

void rightButtonName (char *buf)
{
	for (int i=65; i<128; i++)
		for (int j=56; j<64; j++)
			ssd1306_DrawPixel(i,j, Black);
			
	ssd1306_SetCursor(65, 56);
	ssd1306_WriteString(buf, Font_7x7, White);
}

void leftButtonName (char *buf)
{
	for (int i=0; i<63; i++)
		for (int j=56; j<64; j++)
			ssd1306_DrawPixel(i,j, Black);
			
	ssd1306_SetCursor(0, 56);
	ssd1306_WriteString(buf, Font_7x7, White);
}

void clearCentralBox(void)
{
	for (int i=0; i<122; i++)
		for (int j=9; j<55;j++)
			ssd1306_DrawPixel(i, j, Black);
}

void centralBoxText(char *buf, int startLine, int len)
{
	int realStartLine=9+(startLine)*18;
	int lenghtLine = 10;
	ssd1306_SetCursor(0, realStartLine);
	if (len<lenghtLine)
		ssd1306_WriteString(buf, Font_11x18, White);
	else
	{
		int i=0, line=0;
		while (i<len)
		{
			ssd1306_SetCursor(11*i-(110*line), realStartLine+(line*18));
			ssd1306_WriteChar(buf[i], Font_11x18, White);
			i++;
			if (i%10==0)	
			{		
				line++;
			}
		}
	}
}

void focusButtonIcon (bool press)
{
	int leftPos=40;
	if (!press)
	{
		draw(leftPos, 1, 0x3800);
		draw(leftPos, 2, 0x7C00);
		draw(leftPos, 3, 0x7C00);
		draw(leftPos, 4, 0x7C00);
		draw(leftPos, 5, 0x7C00);
	}
	else
	{
		draw(leftPos, 4, 0x7C00);
		draw(leftPos, 5, 0x7C00);
		draw(leftPos, 3, 0x3800);
		draw(leftPos, 1, 0x0000);	
		draw(leftPos, 2, 0x0000);			
	}
}

void shootButtonIcon (bool press)
{
	int leftPos=48;
	if (!press)
	{
		draw(leftPos, 1, 0x3800);
		draw(leftPos, 2, 0x7C00);
		draw(leftPos, 3, 0x7C00);
		draw(leftPos, 4, 0x7C00);
		draw(leftPos, 5, 0x7C00);
	}
	else
	{
		draw(leftPos, 4, 0x7C00);
		draw(leftPos, 5, 0x7C00);
		draw(leftPos, 3, 0x3800);
		draw(leftPos, 1, 0x0000);	
		draw(leftPos, 2, 0x0000);			
	}
}

void photoCounter (int count)
{
	char buf[6]="     \0";
	int leftPos=65, bufC=count, i=0;
	for (int ii=leftPos; ii<(leftPos+36); ii++)
		for (int j=0; j<8; j++)
			ssd1306_DrawPixel(ii, j, Black);
	ssd1306_SetCursor(leftPos, 0);
	if (count == 0)
	{
		ssd1306_WriteString("   0", Font_7x7, White);
	}
	else{
		while (bufC>0)
		{
			buf[4-i]=(bufC%10)+'0';
			i++;
			bufC/=10;
		}
		buf[5]='\0';
		ssd1306_WriteString(buf, Font_7x7, White);		
	}		
}

void ssd1306_WriteIntOnCentralBox(int count, int xpos, int ypos)
{
	char buf[6]="     \0";
	int bufC=count, i=0;
	ssd1306_SetCursor(xpos, ypos+9);
	if (count == 0)
	{
		ssd1306_WriteString("   0", Font_11x18, White);
	}
	else{
		while (bufC>0)
		{
			buf[4-i]=(bufC%10)+'0';
			i++;
			bufC/=10;
		}
		buf[5]='\0';
		ssd1306_WriteString(buf, Font_11x18, White);		
	}	
}