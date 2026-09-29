#include "main.h"
#include "utils.h"


#include "gpio.h"
#include "can.h"
#include "odo.h"




uint8_t ubKeyNumberValue = 0x0;
uint32_t dernier_envoi_can = 0;

uint8_t motif_actuel = 0;
uint32_t dernier_clignotement_alterne = 0;



void setup(){
		FDCAN_Config();
	ubKeyNumberValue = 0x4;

}

void loop(){
	test_led_bouton();

	test_can();
	if (motif_actuel == 4)
	{
		if (HAL_GetTick() - dernier_clignotement_alterne >= 250)
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11); // Inverse la Verte
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // Inverse la Bleue
			dernier_clignotement_alterne = HAL_GetTick();
		}
	}
}


