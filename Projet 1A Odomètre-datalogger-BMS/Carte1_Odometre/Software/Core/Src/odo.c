#include "odo.h"
#include "main.h" // Pour avoir accès aux fonctions HAL et aux GPIO

#define NB_FENTES 20.0
#define DIAMETRE_ROUE 0.065

// On déclare les variables pour mesurer le temps réel
uint32_t position_precedente = 0;
uint32_t dernier_clignotement = 0;
uint16_t periode_clignotement = 1000;
float rpm_global = 0.0; // On stocke la vitesse dans une variable globale

// CETTE FONCTION FAIT TOURNER LA LED EN CONTINU (Appelée à chaque tour de while)
void rafraichir_led_odometrie() {
	if (rpm_global > 5.0) {
		// Formule mathématique directe pour lier vitesse et clignotement
		periode_clignotement = (uint16_t)(30000.0 / rpm_global);

		if(periode_clignotement < 30) periode_clignotement = 30;   // Max 33 Hz (très rapide)
		if(periode_clignotement > 1000) periode_clignotement = 1000; // Min 1 Hz (lent)

		if (HAL_GetTick() - dernier_clignotement >= periode_clignotement) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11); // LED ODO (PA11)
			dernier_clignotement = HAL_GetTick();
		}
	} else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); // Éteint à l'arrêt
	}
}

// CETTE FONCTION NE FAIT QUE LE CALCUL (Appelée toutes les 100ms)
float obtenir_vitesse_rpm(TIM_HandleTypeDef *htim) {
	uint32_t position_actuelle = __HAL_TIM_GET_COUNTER(htim);
	int32_t diff = (int32_t)(position_actuelle - position_precedente);
	position_precedente = position_actuelle;

	if (diff < 0) diff = -diff;

	if (diff > 0) {
		rpm_global = ((float)diff / NB_FENTES) * 600.0;
	} else {
		rpm_global = 0.0;
	}

	return rpm_global;
}
