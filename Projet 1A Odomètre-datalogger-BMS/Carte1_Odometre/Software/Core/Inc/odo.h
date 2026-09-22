#ifndef ODO_H_
#define ODO_H_

#include "stm32c0xx_hal.h" // Ou votre série de STM32 pour reconnaitre TIM_HandleTypeDef

// Prototype pour le calcul de la vitesse (appelé toutes les 100ms)
float obtenir_vitesse_rpm(TIM_HandleTypeDef *htim);

// Prototype pour la gestion de la LED (appelé en boucle continue)
void rafraichir_led_odometrie(void);

#endif
