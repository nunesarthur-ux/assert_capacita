/******************************************************************************
 * @file LedPwm.h
 * @brief Biblioteca responsável pelo controle dos LEDs PWM.
 ******************************************************************************/

#ifndef _LEDPWM_H_
#define _LEDPWM_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/
/*******************************************************************************
* TIPOS DE DADOS PÚBLICOS
******************************************************************************/

typedef enum
{
eLED_1,
eLED_2,
eLED_3

} led_t;

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/

/**
 * @brief Inicializa o módulo PWM.
 */
void LedPwm_Init(void);

/**
 * @brief Atualiza o brilho dos LEDs.
 */
void LedPwm_Update(void);

/**
 * @brief Habilita ou desabilita o controle dos LEDs.
 */

/**
 * @brief Seleciona qual LED será controlado.
 *
 * @param led LED selecionado.
 */
void LedPwm_SetLed(led_t led);

#endif /* _LEDPWM_H_ */
