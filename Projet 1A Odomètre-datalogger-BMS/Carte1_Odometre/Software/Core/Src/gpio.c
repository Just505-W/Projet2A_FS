#include "gpio.h"
#include "main.h"

void test_led_bouton(){
	int etat = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,etat);
	HAL_Delay(250);

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1-etat);
	HAL_Delay(250);



}
