/******************************************************************************/
/**
 * @file LevelSensor.h
 * @addtogroup LEVEL_SENSOR
 * @{
 ******************************************************************************/

#ifndef INC_LEVELSENSOR_H_
#define INC_LEVELSENSOR_H_



/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * DEFINES PUBLICOS
 ******************************************************************************/

#define dLEVEL_SENSOR_NUMBER_OF_SAMPLES     20U

#define dLEVEL_SENSOR_ADC_MAX               4095U

#define dLEVEL_SENSOR_REFERENCE_VOLTAGE     3.3f

/*******************************************************************************
 * PROTOTIPOS PUBLICOS
 ******************************************************************************/

void LevelSensor_Init(void);

void LevelSensor_NewSample(uint16_t rawValue);

bool LevelSensor_IsReady(void);

float LevelSensor_GetVoltage(void);

float LevelSensor_GetPercentage(void);

void LevelSensor_Reset(void);

void LevelSensor_Task(void);


#endif

/** @} */
