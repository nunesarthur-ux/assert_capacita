/******************************************************************************
 * @file Bsp.h
 * @brief Biblioteca de abstração do hardware.
 *
 * Todas as funções que acessam diretamente o hardware estão neste módulo.
 ******************************************************************************/
#ifndef INC_BSP_H_
#define INC_BSP_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/

#include <stdbool.h>
#include "AssertTypes.h"
#include "LedPwm.h"

/*******************************************************************************
 * DEFINES PÚBLICOS
 ******************************************************************************/

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/

/*--------------------- ADC ---------------------*/

/**
 * @brief Inicia o ADC.
 * @retval Nenhum.
 */
void Bsp_StartAdc(void);

/**
 * @brief Lê o valor do ADC por polling.
 * @return Valor convertido de 12 bits pelo ADC.
 */
u16 Bsp_GetAdc(void);

/*--------------------- PWM ---------------------*/

/**
 * @brief Inicia os canais PWM.
 * @retval Nenhum.
 */
void Bsp_StartPwm(void);

/**
 * @brief Altera o duty cycle de um LED.
 * @param led: LED que será alterado (eLED_1, eLED_2, eLED_3).
 * @param duty: Duty cycle de 0 a 100%.
 * @retval Nenhum.
 */
void Bsp_SetLedDuty(led_t led, u8 duty);

/*--------------------- USART ---------------------*/

/**
 * @brief Inicia a recepção serial por interrupção.
 * @retval Nenhum.
 */
void Bsp_StartSerialReception(void);

/**
 * @brief Envia uma string pela USART de forma bloqueante.
 * @param str: String a ser enviada.
 * @retval Nenhum.
 */
void Bsp_SendString(char *str);

/**
 * @brief Verifica se chegou um novo caractere.
 * @return true se chegou um caractere, false caso contrário.
 */
bool Bsp_IsSerialDataReady(void);

/**
 * @brief Retorna o último caractere recebido e limpa a flag de pronto.
 * @return Caractere recebido.
 */
char Bsp_GetSerialChar(void);

/*--------------------- BOTÃO ---------------------*/

/**
 * @brief Lê o estado lógico atual do pino do botão.
 * @return true se estiver pressionado.
 */
bool Bsp_ReadButton(void);

/**
 * @brief Verifica se ocorreu interrupção externa do botão.
 * @return true se ocorreu a interrupção.
 */
bool Bsp_IsButtonFlag(void);

/**
 * @brief Limpa a flag de interrupção do botão.
 * @retval Nenhum.
 */
void Bsp_ClearButtonFlag(void);

/*--------------------- TIMER ---------------------*/

/**
 * @brief Inicia o timer de amostragem por interrupção.
 * @retval Nenhum.
 */
void Bsp_StartSampleTimer(void);

/**
 * @brief Verifica se o período de amostragem estourou.
 * @return true quando houver nova amostragem.
 */
bool Bsp_IsSampleFlag(void);

/**
 * @brief Limpa a flag de amostragem.
 * @retval Nenhum.
 */
void Bsp_ClearSampleFlag(void);

/**
 * @brief: Inicia o Debounce Timer
 * @retval Nenhum
 */
void Bsp_StartDebounceTimer(void);

/**
 * @brief Verifica se o timer de debounce finalizou.
 * @return true quando o timer de debounce finalizar.
 */
bool Bsp_IsDebounceFlag(void);

/**
 * @brief Limpa a flag de debounce.
 * @retval Nenhum.
 */
void Bsp_ClearDebounceFlag(void);

#endif /* INC_BSP_H_ */
