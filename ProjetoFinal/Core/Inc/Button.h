/******************************************************************************
 * @file Button.h
 * @brief Biblioteca responsável pelo controle do botão.
 ******************************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/

/**
 * @brief Inicializa o módulo do botão.
 */
void Button_Init(void);

/**
 * @brief Atualiza o estado do botão.
 */
void Button_Update(void);

/**
 * @brief Retorna se o sistema está congelado.
 *
 * @return true quando o sistema estiver congelado.
 */
bool Button_IsFrozen(void);


#endif /* INC_BUTTON_H_ */
