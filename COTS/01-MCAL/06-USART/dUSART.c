#include "STD_TYPES.h"
#include <dUSART.h>



/*****************************************/
/********** REGISTERS ADDRESSES **********/
/*****************************************/

/* Peripheral base + BUS + UART LOCATION */
#define     USARTX_1               ((USART_TypeDef *) (((u32)0x40000000) + 0x10000) + 0x3800))
#define     USARTX_2               ((USART_TypeDef *) ((u32)0x40000000) + 0x4400))
#define     USARTX_3               ((USART_TypeDef *) ((u32)0x40000000) + 0x4800))

#define     TXEIE_MASK             (((u16)0x0080))
#define     RXNEIE_MASK            (((u16)0x0020))
#define     USARTx_CR1_CLEAR_MASK  (((u16)0xD853))
#define     USARTx_CR2_CLEAR_MASK  (((u16)0xC1FF))
#define     USART_EN_MASK          (((u16)0x2000))

/*****************************************/
/**************** MASKS ******************/
/*****************************************/



/*****************************************/
/************** VARIABLES ****************/
/*****************************************/



/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
void dUSART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct){

    /* Applying CR1 Configurations */
    u16 Tmp_CR1 = ((USARTx->CR1 )&(USARTx_CR1_CLEAR_MASK));
    Tmp_CR1 |= USART_InitStruct->USART_Parity | USART_InitStruct->USART_Mode | USART_EN_MASK;
    if (USART_InitStruct->USART_TxRxMode & USART_TxRxMode_Rx > 0){
        Tmp_CR1 |= RXNEIE_MASK ;
    }
    if (USART_InitStruct->USART_TxRxMode & USART_TxRxMode_Tx > 0){
        Tmp_CR1 |= TXEIE_MASK ;
    }
    USARTx->CR1  = Tmp_CR1;


    /* Applying CR2 Configurations */
    u16 Tmp_CR2 = ((USARTx->CR2 )&(USARTx_CR2_CLEAR_MASK));
    Tmp_CR2 |= USART_InitStruct->USART_Mode | USART_InitStruct->USART_StopBits ;
    USARTx->CR2  = Tmp_CR2;
    
    
    /* Applying CR3 Configurations */
    ///////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
}


void dUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity   = USART_Parity_No ;
  USART_InitStruct->USART_TxRxMode = USART_TxRxMode_Rx | USART_TxRxMode_Tx;
  USART_InitStruct->USART_Mode     = USART_Mode_Async;
  
}


void dUSART_SendByte(USART_TypeDef* USARTx,u8 Data){
    USARTx->DR = Data;
}


u8 dUSART_ReceiveByte(USART_TypeDef* USARTx){
    return USARTx->DR ;
}

 
FlagStatus dUSART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG){
    FlagStatus BitStatus;
    if (((USARTx->SR)&USART_FLAG) == 0){
        BitStatus = RESET;
    }else{
        BitStatus = SET;
    }
    return BitStatus;
}
