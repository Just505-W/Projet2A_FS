/*
 * led.c
 *
 *  Created on: May 21, 2026
 *      Author: Amélie
 */

#include "main.h"
#include "led.h"
#include <stdio.h>

int led = 0 ;


void setup(void){
	int led = 0 ;
	int compteur = 0 ;
}

void Led_blink(){
	HAL_Delay(250);
	led =1-led;
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, led);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, led);

}

void loop(void){
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1){
		Led_blink();
		}

	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0){
		}
	if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_0)==1 && HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_1)==1){
				printf("LIGHTS ON \n\r");
			}
		else{
				printf("LIGHTS OFF \n\r");
			}
}




