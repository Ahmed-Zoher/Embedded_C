/************************************************************/
/*                                                          */
/*        Author	:	AHMED ZOHER	& WALEED ADEL           */
/*        Version	: 	V01				                    */
/*        Date		:	14 Mar 2020		                    */
/*                                                          */
/************************************************************/

/************************************************************/
/*********************** HEADER GUARD ***********************/
/************************************************************/

#ifndef hUSART_H
#define hUSART_H

/************************************************************/
/****************** HEADER-FILES INCLUSION ******************/
/************************************************************/

#include "dUSART.h"

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define USART1        0
#define USART2        1
#define USART3        2

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef void(*CallBackFn)(void);

/************************************************************/
/****************** VARIABLES DECLARATIONS ******************/
/************************************************************/



/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern void hUSART_Init(u8 USARTx, USART_InitTypeDef * USART_InitStruct);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern u8 hUSART_Send(u8 USARTx,u8 * Data , u32 DataLength);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern u8 hUSART_Receive(u8 USARTx,u8 * Data , u32 DataLength);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern void hUART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack);

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
extern void hUART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack);


#endif















