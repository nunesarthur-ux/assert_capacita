/******************************************************************************/
/**
 * @file LevelSensor.c
 * @addtogroup LEVEL_SENSOR
 * @brief Processamento do nivel do tanque.
 * @{
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "LevelSensor.h"
#include "Bsp.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/
static struct
{
    uint32_t accumulator;
    uint16_t sampleCount;
    uint16_t averageRaw;
    bool newResult;

} levelSensor;

/*******************************************************************************
 * FUNCOES PUBLICAS
 ******************************************************************************/

/******************************************************************************/
/** @brief Inicializa modulo.
 ******************************************************************************/
void LevelSensor_Init(void)
{
    levelSensor.accumulator = 0U;
    levelSensor.sampleCount = 0U;
    levelSensor.averageRaw = 0U;
}

/******************************************************************************/
/** @brief Adiciona nova amostra.
 * @param rawValue: valor bruto do ADC.
 ******************************************************************************/
void LevelSensor_NewSample(uint16_t rawValue)
{
    levelSensor.accumulator += rawValue;

    levelSensor.sampleCount++;
}

/******************************************************************************/
/** @brief Verifica se ha 20 amostras.
 * @retval bool.
 ******************************************************************************/
bool LevelSensor_IsReady(void)
{
    bool ready = false;

    if(levelSensor.sampleCount >=
       dLEVEL_SENSOR_NUMBER_OF_SAMPLES)
    {
        levelSensor.averageRaw =
            levelSensor.accumulator /
            dLEVEL_SENSOR_NUMBER_OF_SAMPLES;

        ready = true;
    }

    return ready;
}

/******************************************************************************/
/** @brief Retorna tensao media.
 * @retval float.
 ******************************************************************************/
float LevelSensor_GetVoltage(void)
{
    return ((float)levelSensor.averageRaw *
            dLEVEL_SENSOR_REFERENCE_VOLTAGE) /
            dLEVEL_SENSOR_ADC_MAX;
}

/******************************************************************************/
/** @brief Retorna percentual do tanque.
 * @retval float.
 ******************************************************************************/
float LevelSensor_GetPercentage(void)
{
    return ((float)levelSensor.averageRaw *
            100.0f) /
            dLEVEL_SENSOR_ADC_MAX;
}

/******************************************************************************/
/** @brief Reinicia acumuladores.
 * @retval Nenhum.
 ******************************************************************************/
void LevelSensor_Reset(void){
    levelSensor.accumulator = 0U;
    levelSensor.sampleCount = 0U;
    levelSensor.averageRaw = 0U;
}

bool LevelSensor_HasNewResult(void){
    bool result;
    result = levelSensor.newResult;
    levelSensor.newResult = false;
    return result;
}

void LevelSensor_Task(void){
    uint16_t rawValue;
    rawValue = Bsp_ReadAdcPolling();
    levelSensor.accumulator += rawValue;
    levelSensor.sampleCount++;

    if(levelSensor.sampleCount >= dLEVEL_SENSOR_NUMBER_OF_SAMPLES){
        levelSensor.averageRaw =
        levelSensor.accumulator /
        dLEVEL_SENSOR_NUMBER_OF_SAMPLES;
        levelSensor.accumulator = 0U;
        levelSensor.sampleCount = 0U;
        levelSensor.newResult = true;
    }
}
/** @} */
