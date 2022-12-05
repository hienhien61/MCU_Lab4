/*
 * functions.c
 *
 *  Created on: Dec 5, 2022
 *      Author: PC PHUONG
 */
#include "functions.h"

void clearLed(){
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
}

void led1(){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void led2(){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

void led3(){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void led4(){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void led5(){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}

void led_oneshot(){
	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
}
void led_but(){
	if(isButton1Pressed()){
		HAL_GPIO_TogglePin(LED7_GPIO_Port, LED7_Pin);
	}
}



