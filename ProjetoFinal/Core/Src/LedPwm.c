/******************************************************************************
 * @file LedPwm.c
 * @brief Biblioteca responsável pelo controle dos LEDs PWM.
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "LedPwm.h"
#include "Bsp.h"
#include "Sampler.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
******************************************************************************/
static struct
{
    led_t selectedLed;
    bool enabled;
    uint8_t duties[3];

} ledPwm;
/*******************************************************************************
 * FUNÇÕES PÚBLICAS
******************************************************************************/

/******************************************************************************
 * @brief Inicializa o módulo.
 ******************************************************************************/
void LedPwm_Init(void)
{
    ledPwm.enabled = true;
    Bsp_StartPwm();
    ledPwm.selectedLed = eLED_1;
}

/******************************************************************************
* @brief Seleciona qual LED será controlado.
******************************************************************************/
void LedPwm_SetLed(led_t led)
{
	ledPwm.selectedLed = led;
}

/******************************************************************************
 * @brief Atualiza o brilho dos LEDs.
 ******************************************************************************/
void LedPwm_Update(void)
{
    int brightness;

    if(ledPwm.enabled == true)
    {
        brightness = Sampler_GetPercentage();
    }
    else
    {
        brightness = 0;
    }

    Bsp_SetLedDuty(ledPwm.selectedLed,brightness);
}

/******************************************************************************
 * @brief Alterna o estado dos LEDs.
 ******************************************************************************/
led_t LedPwm_GetSelected(void)
{
    return ledPwm.selectedLed;
}

uint8_t LedPwm_GetDuty(led_t led)
{
	if (led >= eLED_1 && led <= eLED_3)
	    {
	        return ledPwm.duties[led];
	    }
	    return 0; // Retorna o valor atualizado de forma simples
}
