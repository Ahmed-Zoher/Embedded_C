#include "STD_TYPES.h"
#include <dUSART.h>




/*****************************************/
/********** REGISTERS ADDRESSES **********/
/*****************************************/



/*****************************************/
/**************** MASKS ******************/
/*****************************************/
#define     TXEIE_MASK             (((u16)0x0080))
#define     TCIE_MASK              (((u16)0x0040))
#define     RXNEIE_MASK            (((u16)0x0020))
#define     USARTx_CR1_CLEAR_MASK  (((u16)0xD853))
#define     USARTx_CR2_CLEAR_MASK  (((u16)0xC1FF))
#define     USART_EN_MASK          (((u16)0x2000))
#define     SR_TC_FLAG_CLEAR_MASK  (((u16)0xFFBF))
#define     SR_RXNE_FLAG_CLEAR_MASK (((u16)0xFFDF))
/*****************************************/
/************** VARIABLES ****************/
/*****************************************/



/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
void dUSART_Init(USART_typeDef* USARTx, USART_InitTypeDef* USART_InitStruct , u8 Bus_Clock_MHz){

    /* Applying CR1 Configurations */
    u16 Tmp_CR1 = ((USARTx->CR1 )&(USARTx_CR1_CLEAR_MASK));
    Tmp_CR1 |= USART_InitStruct->USART_Parity | USART_InitStruct->USART_TxRxMode | USART_EN_MASK;
    if (((USART_InitStruct->USART_TxRxMode) & (USART_TxRxMode_Rx)) > 0){
        Tmp_CR1 |= RXNEIE_MASK ;
    }
    if (((USART_InitStruct->USART_TxRxMode) & (USART_TxRxMode_Tx)) > 0){
        Tmp_CR1 |= TCIE_MASK;
    }
    USARTx->CR1  = Tmp_CR1;

    /*clearing TC */
    USARTx->SR &= SR_TC_FLAG_CLEAR_MASK;

    /* Applying CR2 Configurations */
    u16 Tmp_CR2 = ((USARTx->CR2 )&(USARTx_CR2_CLEAR_MASK));
    Tmp_CR2 |= USART_InitStruct->USART_Mode | USART_InitStruct->USART_StopBits ;
    USARTx->CR2  = Tmp_CR2;
    
    
    /* Applying CR3 Configurations */
    
    /*           Not Used          */
    
    /*  Baud rate values in BRR Configurations  */
    	f32 baudrate =(f32) USART_InitStruct->USART_BaudRate;
    	f32 Bus_Clock_Hz = (f32) (Bus_Clock_MHz * 1000000);

    	f32 DIV_total = Bus_Clock_Hz/(16 * baudrate) ;
    	u32 DIV_dec = (u32) DIV_total;
    	f32 DIV_frac= DIV_total - (f32)DIV_dec;
    	f32 DIV_frac_16 = DIV_frac * 16;
    	u32 DIV_frac_16_rounded;
    	if (DIV_frac_16 > ((u32)DIV_frac_16)+0.49){
    		DIV_frac_16_rounded = ((u32)DIV_frac_16)+1;
    	}else{
    		DIV_frac_16_rounded = ((u32)DIV_frac_16);
    	}

    	u32 BRR = (DIV_dec<<4)+DIV_frac_16_rounded;
       	USARTx->BRR  = (u16)BRR;
}


void dUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity   = USART_Parity_No ;
  USART_InitStruct->USART_TxRxMode = USART_TxRxMode_Rx | USART_TxRxMode_Tx;
  USART_InitStruct->USART_Mode     = USART_Mode_Async;
  
}


void dUSART_SendByte(USART_typeDef* USARTx,u8 Data){
    USARTx->DR = Data;
}

void dUSART_ClearTCFlag(USART_typeDef* USARTx){
    USARTx->SR &= SR_TC_FLAG_CLEAR_MASK;

}


u8 dUSART_ReceiveByte(USART_typeDef* USARTx){
    return USARTx->DR;
}

 
FlagStatus_t dUSART_GetFlagStatus(USART_typeDef* USARTx, u16 USART_FLAG){
	FlagStatus_t BitStatus;
    if (((USARTx->SR)&USART_FLAG) == 0){
        BitStatus = Reset;
    }else{
        BitStatus = Set;
    }
    return BitStatus;
}
