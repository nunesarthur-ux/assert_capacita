/******************************************************************************
 * @file SerialCmd.c
 * @brief Biblioteca responsável pelo tratamento dos comandos da USART.
 ******************************************************************************/

#include "SerialCmd.h"
#include "Bsp.h"
#include "LedPwm.h"

/*******************************************************************************
 * ESTRUTURAS DE DADOS LOCAIS
 ******************************************************************************/
static struct
{
    char command[5]; // OTIMIZAÇÃO: Aumentado para 5 para dar margem de segurança
    int index;

} serialCmd;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

void SerialCmd_Init(void)
{
    serialCmd.index = 0;
    for(int i = 0; i < 5; i++) serialCmd.command[i] = 0;
}

void SerialCmd_Update(void)
{
    char c;

    if(Bsp_IsSerialDataReady())
    {
        c = Bsp_GetSerialChar();

        // Ignora quebras de linha soltas (\r ou \n) para não quebrar o alinhamento do texto
        if (c == '\r' || c == '\n')
        {
            return;
        }

        // Armazena o caractere se ainda houver espaço no buffer
        if (serialCmd.index < 4)
        {
            serialCmd.command[serialCmd.index] = c;
            serialCmd.index++;
        }

        // Quando coletar exatamente as 4 letras (Ex: L, E, D, 3)
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
                    LedPwm_SetLed(eLED_3); // Agora vai disparar com total precisão!
                }
            }

            // Reseta o índice para esperar o próximo comando
            serialCmd.index = 0;
        }
    }
}
