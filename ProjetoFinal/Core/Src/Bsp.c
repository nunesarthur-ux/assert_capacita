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
 * DECLARAÇÕES EXTERN - INDICAÇÕES DE VARIÁVEISS
 ******************************************************************************/
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3; // PWM
extern TIM_HandleTypeDef htim6; // Amostragem (5ms)
extern TIM_HandleTypeDef htim7; // Debounce do Botão
extern UART_HandleTypeDef huart3;

static u8 led1_duty = 0;
static u8 led2_duty = 0;
static u8 led3_duty = 0;
static u32 pwm_counter = 0; // Contador que vai de 0 a 100

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
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1);
}

/*---------------- PWM ----------------*/

void Bsp_StartPwm(void)
{
	led1_duty = 0;
	led2_duty = 0;
	led3_duty = 0;
}

void Bsp_SetLedDuty(led_t led, u8 duty)
{
	if(duty > PWM_MAX) duty = PWM_MAX;
	    switch(led)
	    {
	        case eLED_1: led1_duty = duty;
	        break;
	        case eLED_2: led2_duty = duty;
	        break;
	        case eLED_3: led3_duty = duty;
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
    HAL_UART_Transmit(&huart3,(uint8_t *)str,strlen(str),HAL_MAX_DELAY);
}

bool Bsp_IsSerialDataReady(void)
{
    return bsp.serialDataReady;
}

char Bsp_GetSerialChar(void)
{
	char tmp = bsp.serialChar;
    bsp.serialDataReady = false;
    return tmp;
}

/*---------------- BOTÃO ----------------*/

bool Bsp_ReadButton(void)
{

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
bool Bsp_IsDebounceFlag(void)
{
    return bsp.debounceFlag;
}

void Bsp_ClearDebounceFlag(void)
{
    bsp.debounceFlag = false;
}

/*---------------- TIMER ----------------*/

void Bsp_StartSampleTimer(void)
{
    HAL_TIM_Base_Start_IT(&htim6);
}

void Bsp_StartDebounceTimer(void)
{
	__HAL_TIM_SET_COUNTER(&htim7, 0);
    HAL_TIM_Base_Start_IT(&htim7); // ADICIONADO: Agora inicia o TIM7 para o debounce
}

bool Bsp_IsSampleFlag(void)
{
    return bsp.sampleFlag;
}

void Bsp_ClearSampleFlag(void)
{
    bsp.sampleFlag = false;
}


/*******************************************************************************
 * FUNÇÕES LOCAIS
 ******************************************************************************/

/*******************************************************************************
 * CALLBACKS DA HAL
 ******************************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
/* Timer de amostragem */
	if(htim->Instance == TIM6)
	{
		bsp.sampleFlag = true;
		pwm_counter++;
		if(pwm_counter >= 5){
			pwm_counter = 0;
		}
		if(led1_duty > pwm_counter)
	        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		else
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		        // Controle do LED 2 (Pino PB7 - Azul)
		if(led2_duty > pwm_counter)
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
		        // Controle do LED 3 (Pino PB14 - Vermelho)
		if(led3_duty > pwm_counter)
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	}

	if(htim->Instance == TIM7)
	{
		bsp.debounceFlag = true;
		HAL_TIM_Base_Stop_IT(&htim7);
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
        HAL_UART_Receive_IT(&huart3,(uint8_t *)&bsp.serialChar,1);
    }
}


