/******************************************************************************
 * @file Sampler.h
 * @brief Biblioteca responsável pela aquisição e tratamento das amostras do ADC.
 ******************************************************************************/

#ifndef _SAMPLER_H_
#define _SAMPLER_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/

#include "AssertTypes.h"

/*******************************************************************************
 * CONFIGURAÇÕES
 ******************************************************************************/

/*******************************************************************************
 * DEFINES PÚBLICOS
 ******************************************************************************/

/*******************************************************************************
 * TIPOS DE DADOS PÚBLICOS
 ******************************************************************************/

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/

/**
 * @brief Inicializa o módulo de amostragem.
 */
void Sampler_Init(void);

/**
 * @brief Atualiza a média móvel das amostras.
 *
 * Esta função deve ser chamada sempre que houver
 * uma nova conversão do ADC.
 */
void Sampler_Update(void);

/**
 * @brief Retorna a média das amostras.
 *
 * @return Valor médio do ADC.
 */
u16 Sampler_GetAverage(void);

/**
 * @brief Retorna a média convertida para porcentagem.
 *
 * @return Valor entre 0 e 100.
 */
u8 Sampler_GetPercentage(void);

#endif /* _SAMPLER_H_ */



#endif /* INC_SAMPLER_H_ */
