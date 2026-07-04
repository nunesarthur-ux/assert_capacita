/******************************************************************************
 * @file Button.c
 * @brief Biblioteca responsável pelo controle do botão.
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "Button.h"
#include "Bsp.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

static struct
{
    bool frozen;
    bool waitingDebounce;

} button;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

/******************************************************************************
 * @brief Inicializa o módulo.
 ******************************************************************************/
void Button_Init(void)
{
    button.frozen = false;
    button.waitingDebounce = false;
}

/******************************************************************************
 * @brief Atualiza o estado do botão.
 ******************************************************************************/
void Button_Update(void)
{
    /* Verifica se ocorreu uma interrupção do botão */
    if(Bsp_IsButtonFlag())
    {
        Bsp_ClearButtonFlag();

        button.waitingDebounce = true;
    }

    /* Aguarda o término do debounce */
    if(button.waitingDebounce)
    {
        if(Bsp_IsDebounceFlag())
        {
            Bsp_ClearDebounceFlag();

            button.waitingDebounce = false;

            /* Confirma se o botão continua pressionado */
            if(Bsp_ReadButton())
            {
                button.frozen = !button.frozen;
            }
        }
    }
}

/******************************************************************************
 * @brief Retorna se o sistema está congelado.
 ******************************************************************************/
bool Button_IsFrozen(void)
{
    return button.frozen;
}
