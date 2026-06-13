/******************************************************************************/
/**
 * @file Bsp.c
 * @addtogroup BSP
 * @brief Interface entre aplicacao e hardware.
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "Bsp.h"

#include "adc.h"
#include "tim.h"
#include "usart.h"

#include <stdio.h>

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

static struct
{
    volatile bool timerFlag;

} bsp;

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief Inicializa o modulo BSP.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_Init(void)
{
    bsp.timerFlag = false;
}

/******************************************************************************/
/** @brief Inicia interrupcao do TIM6.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_StartTimerInterrupt(void)
{
    HAL_TIM_Base_Start_IT(&htim6);
}

/******************************************************************************/
/** @brief Retorna estado da flag do timer.
 * @retval bool.
 ******************************************************************************/
bool Bsp_IsTimerFlagSet(void)
{
    return bsp.timerFlag;
}

/******************************************************************************/
/** @brief Limpa flag do timer.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_ClearTimerFlag(void)
{
    bsp.timerFlag = false;
}

/******************************************************************************/
/** @brief Le ADC por polling.
 * @retval uint16_t.
 ******************************************************************************/
uint16_t Bsp_ReadAdcPolling(void)
{
    uint16_t rawValue;

    HAL_ADC_Start(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    rawValue = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    return rawValue;
}

/******************************************************************************/
/** @brief Imprime resultado pela USART.
 * @param voltage: tensao calculada.
 * @param percentage: percentual do tanque.
 * @retval Nenhum.
 ******************************************************************************/
void Bsp_PrintLevel(float voltage,float percentage){
    printf("Nivel: %.1f %% | Tensao: %.2f V\r\n", percentage,voltage);
}
void Bsp_SetTimerFlag(void)
{
    bsp.timerFlag = true;
}

/** @} */
