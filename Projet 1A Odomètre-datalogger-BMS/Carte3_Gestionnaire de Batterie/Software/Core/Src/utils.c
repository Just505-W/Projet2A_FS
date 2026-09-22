#include "main.h"
#include "utils.h"


#include "gpio.h"
#include "can.h"





uint8_t ubKeyNumberValue = 0x0;
uint32_t dernier_envoi_can = 0;




void setup(){

	FDCAN_Config();
	ubKeyNumberValue = 0x4;

}

void loop(){
	test_led_bouton();
	test_can();
	/*if (HAL_GetTick() - dernier_envoi_can >= 500)
	    {
	        // On repasse sur votre fonction test_can standard
	        // (qui envoie ubKeyNumber ou une valeur fixe)
	        test_can();

	        dernier_envoi_can = HAL_GetTick();
	    }*/

}


