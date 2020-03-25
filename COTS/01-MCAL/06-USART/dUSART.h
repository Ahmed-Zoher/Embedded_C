#ifndef dUSART_H
#define dUSART_H


/*****************************************/
/******** VARIABLES DECLARATIONS *********/
/*****************************************/
typedef enum {
    RESET,
    SET
}FlagStatus;


typedef struct
{
  volatile u16 SR;
  u16  RESERVED0;
  volatile u16 DR;
  u16  RESERVED1;
  volatile u16 BRR;
  u16  RESERVED2;
  volatile u16 CR1;
  u16  RESERVED3;
  volatile u16 CR2;
  u16  RESERVED4;
  volatile u16 CR3;
  u16  RESERVED5;
  volatile u16 GTPR;
  u16  RESERVED6;
} USART_TypeDef;

typedef struct
{
  u32 USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                      The baud rate is computed using the following formula:
                                       - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                       - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */
  u16 USART_StopBits;
  u16 USART_Parity;
  u16 USART_TxRxMode;
  u16 USART_Mode;

} USART_InitTypeDef;




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

#define USART_Mode_Async                    ((u16)0x0008)
#define USART_Mode_Sync_Pol_0_Ph_0          ((u16)0x0008)
#define USART_Mode_Sync_Pol_0_Ph_1          ((u16)0x0008)
#define USART_Mode_Sync_Pol_1_Ph_0          ((u16)0x0008)
#define USART_Mode_Sync_Pol_1_Ph_1          ((u16)0x0008)



#define USART1        USARTX_1
#define USART2        USARTX_2
#define USART3        USARTX_3


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

void dUSART_Init(USART_TypeDef* USARTx, USART_InitTypeDef * USART_InitStruct);
void dUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);
void dUSART_SendByte(USART_TypeDef* USARTx,u8 Data);
u8 dUSART_ReceiveByte(USART_TypeDef* USARTx);
FlagStatus dUSART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG);


#endif

