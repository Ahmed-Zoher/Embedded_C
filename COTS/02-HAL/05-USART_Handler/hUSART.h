#ifndef hUSART_H
#define hUSART_H


/*****************************************/
/******** VARIABLES DECLARATIONS *********/
/*****************************************/




/*****************************************/
/*************** DEFINES *****************/
/*****************************************/

#define USART_StopBits_1                     ((u16)0x0000)
#define USART_StopBits_2                     ((u16)0x2000)


#define USART_Parity_No                      ((u16)0x0000)
#define USART_Parity_Even                    ((u16)0x0400)
#define USART_Parity_Odd                     ((u16)0x0600) 

#define USART_TxRxMode_Rx                    ((u16)0x0004)
#define USART_TxRxMode_Tx                    ((u16)0x0008)

#define USART_Mode_Async                     ((u16)0x0008)
#define USART_Mode_Sync_Pol_0_Ph_0           ((u16)0x0008)
#define USART_Mode_Sync_Pol_0_Ph_1           ((u16)0x0008)
#define USART_Mode_Sync_Pol_1_Ph_0           ((u16)0x0008)
#define USART_Mode_Sync_Pol_1_Ph_1           ((u16)0x0008)



#define USART1        0
#define USART2        1
#define USART3        2


#define USART_FLAG_CTS                       ((u16)0x0200)
#define USART_FLAG_LBD                       ((u16)0x0100)
#define USART_FLAG_TXE                       ((u16)0x0080)
#define USART_FLAG_TC                        ((u16)0x0040)
#define USART_FLAG_RXNE                      ((u16)0x0020)
#define USART_FLAG_IDLE                      ((u16)0x0010)
#define USART_FLAG_ORE                       ((u16)0x0008)
#define USART_FLAG_NE                        ((u16)0x0004)
#define USART_FLAG_FE                        ((u16)0x0002)
#define USART_FLAG_PE                        ((u16)0x0001)

/*****************************************/
/********* FUNCTION DECLARATIONS *********/
/*****************************************/

void hUSART_Init(u8 USARTx, USART_InitTypeDef * USART_InitStruct);
void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);
void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct);
u8 hUSART_Send(u8 USARTx,u8 * Data , u32 DataLength);
u8 hUSART_Receive(u8 USARTx,u8 * Data , u32 DataLength);
void hUART_SetTxCallBackFn(void(*TxCallBack)(void));
void hUART_SetRxCallBackFn(void(*RxCallBack)(void));

#endif

