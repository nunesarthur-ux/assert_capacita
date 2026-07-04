/******************************************************************************
 * @file SerialCmd.c
 * @brief Biblioteca responsável pelo tratamento dos comandos da USART.
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "SerialCmd.h"
#include "Bsp.h"
#include "LedPwm.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/

static struct
{
    char command[4];
    int index;

} serialCmd;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

/******************************************************************************
 * @brief Inicializa o módulo.
 ******************************************************************************/
void SerialCmd_Init(void)
{
    serialCmd.index = 0;
}

/******************************************************************************
 * @brief Trata os comandos recebidos pela USART.
 ******************************************************************************/
void SerialCmd_Update(void)
{
    char c;

    if(Bsp_IsSerialDataReady())
    {
        c = Bsp_GetSerialChar();

        serialCmd.command[serialCmd.index] = c;
        serialCmd.index++;

        if(serialCmd.index == 4)
        {
            if(serialCmd.command[0] == 'L' &&  serialCmd.command[1] == 'E' && serialCmd.command[2] == 'D')
            {
                if(serialCmd.command[3] == '1')
                {
                    LedPwm_SetLed(eLED_1);
                }
                else if(serialCmd.command[3] == '2')
                {
                    LedPwm_SetLed(eLED_2);
                }
                else if(serialCmd.command[3] == '3')
                {
                    LedPwm_SetLed(eLED_3);
                }
            }

            serialCmd.index = 0;
        }
    }
}


