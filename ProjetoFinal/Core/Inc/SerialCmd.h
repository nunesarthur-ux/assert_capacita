/******************************************************************************
 * @file SerialCmd.h
 * @brief Biblioteca responsável pelo tratamento dos comandos da USART.
 ******************************************************************************/

#ifndef _SERIALCMD_H_
#define _SERIALCMD_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/

/**
 * @brief Inicializa o módulo.
 */
void SerialCmd_Init(void);

/**
 * @brief Trata os comandos recebidos pela USART.
 */
void SerialCmd_Update(void);



#endif /* INC_SERIALCMD_H_ */
