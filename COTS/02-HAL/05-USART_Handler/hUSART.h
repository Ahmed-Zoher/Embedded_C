

#include "dUSART.h"

/*****************************************/
/******** VARIABLES DECLARATIONS *********/
/*****************************************/

typedef void(*CallBackFn)(void);



/*****************************************/
/*************** DEFINES *****************/
/*****************************************/

#define USART1        0
#define USART2        1
#define USART3        2




/*****************************************/
/********* FUNCTION DECLARATIONS *********/
/*****************************************/

void hUSART_Init(u8 USARTx, USART_InitTypeDef * USART_InitStruct);
void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);
void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct);
u8 hUSART_Send(u8 USARTx,u8 * Data , u32 DataLength);
u8 hUSART_Receive(u8 USARTx,u8 * Data , u32 DataLength);
void hUART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack);
void hUART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack);



