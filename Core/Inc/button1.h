/*
 * button.h
 *
 *  Created on: Nov 2, 2022
 *      Author: PC PHUONG
 */

#ifndef INC_BUTTON1_H_
#define INC_BUTTON1_H_

#include "main.h"

#define NORMAL_STATE 	GPIO_PIN_SET
#define PRESSED_STATE	GPIO_PIN_RESET

int isButton1Pressed();

void getKeyInput();

#endif /* INC_BUTTON1_H_ */
