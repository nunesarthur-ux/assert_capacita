/******************************************************************************
 * @file Button.c
 * @brief Gerenciamento do botão de usuário com debounce por hardware/timer.
 ******************************************************************************/

#include "Button.h"
#include "Bsp.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/
static struct
{
    bool isFrozen;      // Estado atual do sistema (true = travado, false = normal)
    bool awaitingDebounce; // Evita múltiplas interrupções seguidas
} buttonState;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

void Button_Init(void)
{
    buttonState.isFrozen = false;
    buttonState.awaitingDebounce = false;
}

void Button_Update(void)
{
    // 1. Verifica se a interrupção física do botão (EXTI) sinalizou um clique no Bsp
    if (Bsp_IsButtonFlag())
    {
        Bsp_ClearButtonFlag(); // Limpa a flag imediatamente

        // Se já estávamos esperando o tempo de debounce acabar, ignora trepidações
        if (!buttonState.awaitingDebounce)
        {
            buttonState.awaitingDebounce = true;
            Bsp_StartDebounceTimer(); // Dispara o TIM7 (ajustado para uns 50ms)
        }
    }

    // 2. Verifica se o TIM7 terminou de contar o tempo do debounce
    if (Bsp_IsDebounceFlag())
    {
        Bsp_ClearDebounceFlag(); // Limpa a flag do timer

        // O tempo passou! Vamos ler o pino físico de forma segura para confirmar se foi pressionado
        if (Bsp_ReadButton() == true)
        {
            // Alterna o estado do sistema (Toggle): se estava ON vira OFF, se estava OFF vira ON
            buttonState.isFrozen = !buttonState.isFrozen;
        }

        // Libera o botão para receber um novo clique do usuário
        buttonState.awaitingDebounce = false;
    }
}

// Essa função é chamada no main.c para decidir se atualiza ou não os LEDs/ADC
bool Button_IsFrozen(void)
{
    return buttonState.isFrozen;
}
