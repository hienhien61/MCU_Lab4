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

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint16_t matrix_buffer1[8] = {0xF300 , 0xE100 , 0xC100 , 0x8300 , 0x8300 , 0xC100 , 0xE100, 0xF300};
uint16_t matrix_buffer2[8] = {0xF300 , 0xED00 , 0xDD00 , 0xBB00 , 0xBB00 , 0xDD00 , 0xED00, 0xF300};
int state = 0;
void updateLEDMatrix(int index){
	HAL_GPIO_WritePin(GPIOA, 0xFFFF, SET);
	HAL_GPIO_WritePin(GPIOB, 0xFFFF, RESET);

	switch(index){
	case 0: //Cot 0
		HAL_GPIO_WritePin(GPIOA, 0x04, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xFC08, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[0], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[0], SET);
		break;
	case 1: //Cot 1
		HAL_GPIO_WritePin(GPIOA, 0x08, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xFC04, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[1], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[1], SET);
		break;
	case 2: //Cot 2
		HAL_GPIO_WritePin(GPIOA, 0x400, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xF80C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[2], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[2], SET);
		break;
	case 3: //Cot 3
		HAL_GPIO_WritePin(GPIOA, 0x800, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xF40C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[3], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[3], SET);
		break;
	case 4: //Cot 4
		HAL_GPIO_WritePin(GPIOA, 0x1000, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xEC0C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB,matrix_buffer1[4], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[4], SET);
		break;
	case 5: //Cot 5
		HAL_GPIO_WritePin(GPIOA, 0x2000, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xDC0C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[5], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[5], SET);
		break;
	case 6: //Cot 6
		HAL_GPIO_WritePin(GPIOA, 0x4000, RESET);
		HAL_GPIO_WritePin(GPIOA, 0xBC0C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[6], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[6], SET);
		break;
	case 7: //Cot 7
		HAL_GPIO_WritePin(GPIOA, 0x8000, RESET);
		HAL_GPIO_WritePin(GPIOA, 0x7C0C, SET);

		if(state == 0) HAL_GPIO_WritePin(GPIOB, matrix_buffer1[7], SET);
		else HAL_GPIO_WritePin(GPIOB, matrix_buffer2[7], SET);
		break;
	default:
		HAL_GPIO_WritePin(GPIOA, 0xFFFF, RESET);
		HAL_GPIO_WritePin(GPIOA, 0x0000, SET);

		break;
	}
}

void run_matrix(){
	if(index_led_matrix > 7) {
		  index_led_matrix = 0;
		  state = 1 - state;
	}
	updateLEDMatrix(index_led_matrix++);
}


