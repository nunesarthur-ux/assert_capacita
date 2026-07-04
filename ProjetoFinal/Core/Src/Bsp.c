/******************************************************************************
 * @file Bsp.c
 * @brief Biblioteca de abstração do hardware.
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "Bsp.h"
#include "main.h"
#include <string.h>

/*******************************************************************************
 * DEFINES LOCAIS
 ******************************************************************************/

#define PWM_MAX 100

/*******************************************************************************
 * CONSTANTES
 ******************************************************************************/

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

static struct
{
    bool sampleFlag;
    bool buttonFlag;
	bool debounceFlag;
   bool serialDataReady;
    char serialChar;

} bsp;

/*******************************************************************************
 * PROTÓTIPOS LOCAIS
 ******************************************************************************/

static int DutyToCompare(int duty);

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

/*---------------- ADC ----------------*/

void Bsp_StartAdc(void)
{
    HAL_ADC_Start(&hadc1);
}

u16 Bsp_GetAdc(void)
{
    HAL_ADC_Start(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    return HAL_ADC_GetValue(&hadc1);
}

/*---------------- PWM ----------------*/

void Bsp_StartPwm(void)
{
    /* TODO:
     * Confirmar timer e canais no CubeMX.
     */

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void Bsp_SetLedDuty(led_t led, u8 duty)
{
    int compare;

    if(duty > 100)
    {
        duty = 100;
    }

    compare = DutyToCompare(duty);

    switch(led)
    {
        case eLED_1:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, compare);
        break;

        case eLED_2:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, compare);
        break;

        case eLED_3:
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, compare);
        break;
    }
}

/*---------------- USART ----------------*/

void Bsp_StartSerialReception(void)
{
    HAL_UART_Receive_IT(&huart3, (uint8_t *)&bsp.serialChar, 1);
}

void Bsp_SendString(char *str)
{
    HAL_UART_Transmit(&huart3,
                      (uint8_t *)str,
                      strlen(str),
                      HAL_MAX_DELAY);
}

bool Bsp_IsSerialDataReady(void)
{
    return bsp.serialDataReady;
}

char Bsp_GetSerialChar(void)
{
    bsp.serialDataReady = false;

    return bsp.serialChar;
}

/*---------------- BOTÃO ----------------*/

bool Bsp_ReadButton(void)
{
    /* TODO:
     * Alterar porta e pino conforme CubeMX.
     */

    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
    {
        return true;
    }

    return false;
}

bool Bsp_IsButtonFlag(void)
{
    return bsp.buttonFlag;
}

void Bsp_ClearButtonFlag(void)
{
    bsp.buttonFlag = false;
}

/*---------------- TIMER ----------------*/

void Bsp_StartSampleTimer(void)
{
    /* TODO:
     * Confirmar timer utilizado para amostragem.
     */

    HAL_TIM_Base_Start_IT(&htim2);
}

bool Bsp_IsSampleFlag(void)
{
    return bsp.sampleFlag;
}

void Bsp_ClearSampleFlag(void)
{
    bsp.sampleFlag = false;
}
/******************************************************************************
 * @brief Verifica se o debounce terminou.
 ******************************************************************************/
bool Bsp_IsDebounceFlag(void)
{
    return bsp.debounceFlag;
}

/******************************************************************************
 * @brief Limpa a flag de debounce.
 ******************************************************************************/
void Bsp_ClearDebounceFlag(void)
{
    bsp.debounceFlag = false;
}

/*******************************************************************************
 * FUNÇÕES LOCAIS
 ******************************************************************************/

static int DutyToCompare(int duty)
{
    int period;

    /* TODO:
     * Confirmar timer PWM no CubeMX.
     */

    period = __HAL_TIM_GET_AUTORELOAD(&htim3);

    return (period * duty) / PWM_MAX;
}

/*******************************************************************************
 * CALLBACKS DA HAL
 ******************************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
/* Timer de amostragem */
if(htim->Instance == TIM2)
{
bsp.sampleFlag = true;
}

/* TODO:
* Confirmar qual timer será utilizado para o debounce.
*/
if(htim->Instance == TIM4)
{
bsp.debounceFlag = true;

HAL_TIM_Base_Stop_IT(&htim4);
}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* TODO:
     * Confirmar pino do botão.
     */

    if(GPIO_Pin == GPIO_PIN_13)
    {
        bsp.buttonFlag = true;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART3)
    {
        bsp.serialDataReady = true;

        HAL_UART_Receive_IT(&huart3,
                            (uint8_t *)&bsp.serialChar,
                            1);
    }
}


