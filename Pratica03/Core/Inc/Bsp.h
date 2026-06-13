
/******************************************************************************/
/**
 * @file Bsp.h
 * @addtogroup BSP
 * @{
 ******************************************************************************/
#ifndef BSP_H
#define BSP_H

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * DEFINES PUBLICOS
 ******************************************************************************/

#define dBSP_ADC_MAX_VALUE        4095U

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

void Bsp_Init(void);

void Bsp_StartTimerInterrupt(void);

bool Bsp_IsTimerFlagSet(void);

void Bsp_ClearTimerFlag(void);

uint16_t Bsp_ReadAdcPolling(void);

void Bsp_PrintLevel(float voltage, float percentage);

void Bsp_SetTimerFlag(void);
#endif

/** @} */
