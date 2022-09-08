#ifndef FOCUSBUTTON_H_
#define FOCUSBUTTON_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"
#include "stm32f1xx_hal.h"

#define FOCUSBUTTON GPIO_PIN_15
#define SHOOTBUTTON GPIO_PIN_14

void focusButtonSet(void);
bool shootButtonSet (void);
void focusButtonReSet (void);


#endif /* FOCUSBUTTON_H_ */