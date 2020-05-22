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
#include <dUSART.h>
#include "dDMA.h"


/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define USART1                                    0
#define USART2                                    1
#define USART3                                    2
#define UART_MODE_DMA_Enable                      1
#define UART_MODE_DMA_Disable                     0
#define Select_Tx                                 0
#define Select_Rx                                 1
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
/* Input  => u8 {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
extern void hUSART_Init(u8 USARTx, USART_InitTypeDef * USART_InitStruct);

/* Description: This API shall initialize the paramters     */
/*              of the USART_InitStruct needed by the       */
/*              init function using default values          */
/*              this Api is used only upon initializing     */
/*              with default configurations                 */
/*              O.W. the user shall initialize the struct   */
/*              with the required configurations            */
/* Input  => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
extern void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);

/* Description: This API shall Configure UART during runtime*/
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
extern void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct);

/* Description: This API shall Send an array of Bytes       */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => u8 * Data {pointer to data to be transmitted}  */
/*        => u32 DataLength: number of bytes                */
/* Output => u8 {BUFFER_BUSY , BUFFER_IDLE}                 */
extern u8 hUSART_Send(u8 USARTx,u8 * Data , u32 DataLength);

/* Description: This API shall Recieve an array of Bytes    */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => u8 * Data {pointer to data to be Recieved}     */
/*        => u32 DataLength: number of bytes                */
/* Output => u8 {BUFFER_BUSY , BUFFER_IDLE}                 */
extern u8 hUSART_Receive(u8 USARTx,u8 * Data , u32 DataLength);

/* Description: This API shall Set Tx callback Function     */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {TxCallBack}                        */
/* Output => void                                           */
extern void hUSART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack);

/* Description: This API shall Set Rx callback Function     */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {RxCallBack}                        */
/* Output => void                                           */
extern void hUSART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack);

/* Description: This API shall Set LIN break detection    
   callback Function                                        */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {LINCallBack}                       */
/* Output => void                                           */
extern void hUART_SetLIN_BreakCallBackFn(u8 USARTx,CallBackFn LINCallBack);

/* Description: This API shall Configure DMA during runtime */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => DMA_InitTypeDef_t * {parameters for configs}   */
/* Output => void                                           */
extern void hUSART_ConfigureDMA_mode(u8 USARTx, DMA_InitTypeDef_t * DMA_USART_Configure);

/* Description: This API shall Send LIN break               */
/* Input  => void                                           */
/* Output => void                                           */
extern void hUSART_SendLIN_Break(u8 USARTx);

#endif















