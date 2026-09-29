#include "can.h"
#include "main.h"


#include <stdio.h>

/*imports CAN*/
#include "stm32c0xx_hal_def.h"
#include "stm32c0xx.h"
#include "Legacy/stm32_hal_legacy.h"   /* Aliases file for old names compatibility */
#include <stddef.h>




extern FDCAN_HandleTypeDef hfdcan1;

uint8_t ubKeyNumber = 0x0;
FDCAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
FDCAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8];

volatile uint8_t derniere_valeur_recue = 0;



void FDCAN_Config(){
	FDCAN_FilterTypeDef sFilterConfig;

	/* Configure Rx filter */
	sFilterConfig.IdType = FDCAN_STANDARD_ID;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x123;
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
	TxHeader.Identifier = 0x123;
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
    // On prépare les données à envoyer (ID 0x123 pour la Carte B)
    TxData[0] = ubKeyNumber;
    for(int i = 1; i < 8; i++){
        TxData[i] = (uint8_t) 66;
    }

    // On met le message dans la FIFO sans toucher aux LED
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData);
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
    {
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
        {
            // La LED PA11 clignote UNIQUEMENT si un message physique valide est reçu
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);

            derniere_valeur_recue = RxData[0];
        }
    }
}
