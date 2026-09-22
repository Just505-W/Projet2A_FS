 #include "can.h"
#include "main.h"


#include <stdio.h>

/*imports CAN*/
#include "stm32c0xx_hal_def.h"
#include "stm32c0xx.h"
#include "Legacy/stm32_hal_legacy.h"   /* Aliases file for old names compatibility */
#include <stddef.h>

#include "odo.h"   //Odo
extern TIM_HandleTypeDef htim2;  //Odo

extern FDCAN_HandleTypeDef hfdcan1;

uint8_t ubKeyNumber = 0x0;
FDCAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
FDCAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8];

volatile uint8_t derniere_valeur_recue = 0;

extern uint8_t motif_actuel;
extern uint32_t dernier_clignotement_alterne;



void FDCAN_Config(){
	FDCAN_FilterTypeDef sFilterConfig;

	/* Configure Rx filter */
	sFilterConfig.IdType = FDCAN_STANDARD_ID;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x321;
	sFilterConfig.FilterID2 = 0x7FF;
	if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}

	/* Prepare Tx Header */
	TxHeader.Identifier = 0x321;
	TxHeader.IdType = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;
}

void test_can(){
	// 1. On rafraîchit le calcul de vitesse
	//float vraie_vitesse = obtenir_vitesse_rpm(&htim2);
	//uint16_t rpm_entier = (uint16_t)vraie_vitesse;

	// 2. On prépare la trame
	TxData[0] = ubKeyNumber; //(rpm_entier >> 8) & 0xFF;
	//TxData[1] = rpm_entier & 0xFF;
	for(int i = 1; i < 8; i++){
		TxData[i] = (uint8_t) 0;

	}
	// 3. TÉMOIN VISUEL : On force le clignotement de la LED CAN (PA5) à CHAQUE tentative d'envoi
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	// 4. Envoi sur le bus
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData);

	// 5. On n'oublie pas de rafraîchir la LED d'odo en tâche de fond
	//rafraichir_led_odometrie();
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
    {
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            // On sauvegarde le numéro de motif reçu dans le premier octet
            motif_actuel = RxData[0];

            // On applique directement les motifs statiques (1, 2 et 3)
            switch (motif_actuel)
            {
                case 1: // LED Verte seule (PA11)
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                    break;

                case 2: // LED Bleue seule (PA5)
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
                    break;

                case 3: // Les deux en même temps
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
                    break;

                case 4: // Motif 4 (Clignotement alterné) -> On initialise l'état de départ ici
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                    break;

                default: // Si on reçoit autre chose, on éteint tout par sécurité
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                    break;
            }
        }
    }
}
