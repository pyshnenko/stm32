#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <stdbool.h>
#include <stdio.h>
#include <cstring>
#include "stm32f1xx_hal.h"

#define MENUSTART			1;

typedef enum
{
	ONESHOOTMODE = 1,
	ENDLESSMODE,
	LIMITEDMODE,
	WIRELESSSET,
	ABOUT,
	BACKMENU
} menusets;

#define TOTALMENU			6;

void setFunction (int function);
void rightButtonPress (int function);
void leftButtonPress (int function);
int checkingNum(int pos, int start);
int endlessMode(int pause, int focus, int total);
void hexToAsciiForSend(uint64_t tube, char *id);
void itoa (int num, char* buf);
void uartSend (char *buf);
void uartSendInt(int buf);
	
#endif /* FUNCTION */