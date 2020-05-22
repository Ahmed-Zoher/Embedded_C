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
#ifndef dUSART_H
#define dUSART_H

/************************************************************/
/************************** MACROS **************************/
/************************************************************/


/* Peripheral base + BUS + UART LOCATION */
#define     USARTx_1               ((USART_typeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))
#define     USARTx_2               ((USART_typeDef *) (((u32)0x40000000) + 0x4400))
#define     USARTx_3               ((USART_typeDef *) (((u32)0x40000000) + 0x4800))


#define USART_StopBits_1                     ((u16)0x0000)
#define USART_StopBits_2                     ((u16)0x2000)


#define USART_Parity_No                      ((u16)0x0000)
#define USART_Parity_Even                    ((u16)0x0400)
#define USART_Parity_Odd                     ((u16)0x0600) 

#define USART_TxRxMode_Rx                    ((u16)0x0004)
#define USART_TxRxMode_Tx                    ((u16)0x0008)

#define USART_DMA_TxRxMode_Disable           ((u16)0x0000)
#define USART_DMA_TxRxMode_Rx                ((u16)0x0040)
#define USART_DMA_TxRxMode_Tx                ((u16)0x0080)

#define USART_Mode_Async                     ((u16)0x0000)
#define USART_Mode_Sync_Pol_0_Ph_0           ((u16)0x0800)
#define USART_Mode_Sync_Pol_0_Ph_1           ((u16)0x0A00)
#define USART_Mode_Sync_Pol_1_Ph_0           ((u16)0x0C00)
#define USART_Mode_Sync_Pol_1_Ph_1           ((u16)0x0E00)

#define USART_LIN_Mode_Enable_10_Bit         ((u16)0x4000)
#define USART_LIN_Mode_Enable_11_Bit         ((u16)0x4020)
#define USART_LIN_Mode_Disable               (0)

#define USART_LIN_Interrupt_Enable           ((u16)0x0040)
#define USART_LIN_Interrupt_Disable          ((u16)0x0000)

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

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/
typedef enum
{
    Reset,
    Set
}FlagStatus_t;

/* UART Peripheral register structure */
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
  
} USART_typeDef;


/* configuration parameters for the UART peripheral */
typedef struct
{
  u32 USART_BaudRate;
  u16 USART_StopBits;
  u16 USART_Parity;
  /* Trasmiter/Receiver Enabled or not */
  u16 USART_TxRxMode;
  /* DMA Trasmiter/Receiver Enabled or not */
  u16 USART_DMA_TxRxMode;
  /* Synchronization, clock polarity and clock phase */
  u16 USART_Mode;
  /* LIN Mode Enabled or not */
  u16 USART_LIN_Mode;
  /* LIN Interrupt Enabled or not */
  u16 USART_LIN_Interrupt;

} USART_InitTypeDef;

/************************************************************/
/****************** VARIABLES DECLARATIONS ******************/
/************************************************************/




/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Bus_Clock_MHz: Input freq to the peripheral    */
/* Output => void                                           */
extern void dUSART_Init(USART_typeDef* USARTx, USART_InitTypeDef * USART_InitStruct, u8 Bus_Clock_MHz);

/* Description: This API shall initialize the paramters     */
/*              of the USART_InitStruct needed by the       */
/*              init function                               */
/* Input  => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
extern void dUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct);

/* Description: This API shall clear the TC flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
void dUSART_ClearLBDFlag(USART_typeDef* USARTx);


/* Description: This API shall send one byte of data        */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => Data   {Byte of data to be sent}               */
/* Output => void                                           */
extern void dUSART_SendByte(USART_typeDef* USARTx,u8 Data);

/* Description: This API shall send one byte of data        */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
extern u8 dUSART_ReceiveByte(USART_typeDef* USARTx);

/* Description: This API shall return the status of flags   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_FLAG   {The flag name: USART_FLAG_x}     */
/* Output => void                                           */
extern FlagStatus_t dUSART_GetFlagStatus(USART_typeDef* USARTx, u16 USART_FLAG);

/* Description: This API shall clear the TC flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
extern void dUSART_ClearTCFlag(USART_typeDef* USARTx);

/* Description: This API shall clear the RXNE flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
extern void dUSART_ClearRXNEFlag(USART_typeDef* USARTx);

/* Description: This API shall Send LIN break               */
/* Input  => void                                           */
/* Output => void                                           */
extern void dUSART_SendLIN_Break(USART_typeDef* USARTx);


#endif

