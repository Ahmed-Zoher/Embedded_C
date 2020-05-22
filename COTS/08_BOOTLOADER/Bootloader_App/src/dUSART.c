/************************************************************/
/*                                                          */
/*        Author	:	AHMED ZOHER	& WALEED ADEL           */
/*        Version	: 	V01				                    */
/*        Date		:	14 Mar 2020		                    */
/*                                                          */
/************************************************************/

/************************************************************/
/****************** HEADER-FILES INCLUSION ******************/
/************************************************************/
#include <STD_TYPES.h>

#include <dUSART.h>





/************************************************************/
/************************** MACROS **************************/
/************************************************************/
#define     TXEIE_MASK              (((u16)0x0080))
#define     TCIE_MASK               (((u16)0x0040))
#define     RXNEIE_MASK             (((u16)0x0020))
#define     USARTx_CR1_CLEAR_MASK   (((u16)0xD853))
#define     USARTx_CR1_SBK_Enable   (((u16)0x0001))
#define     USARTx_CR2_CLEAR_MASK   (((u16)0xC1FF))
#define     USARTx_CR3_CLEAR_MASK   (((u16)0xFF3F))
#define     USART_EN_MASK           (((u16)0x2000))
#define     SR_TC_FLAG_CLEAR_MASK   (((u16)0xFFBF))
#define     SR_LBD_FLAG_CLEAR_MASK  (((u16)0xFEFF))
#define     SR_RXNE_FLAG_CLEAR_MASK (((u16)0xFFDF))



/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/


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
void dUSART_Init(USART_typeDef* USARTx, USART_InitTypeDef* USART_InitStruct , u8 Bus_Clock_MHz){
	
	/*******************************/
    /* Applying CR1 Configurations */
	/*******************************/
    u16 Tmp_CR1 = ((USARTx->CR1 )&(USARTx_CR1_CLEAR_MASK));
    Tmp_CR1    |= USART_InitStruct->USART_Parity | USART_InitStruct->USART_TxRxMode | USART_EN_MASK;
	
	/* checking if the transmitter is enabled */
    if (((USART_InitStruct->USART_TxRxMode) & (USART_TxRxMode_Rx)) > 0){
		/* enabling the transmit complete interrupt */
        Tmp_CR1 |= RXNEIE_MASK ;
    }
	/* checking if the transmitter is enabled */
    if (((USART_InitStruct->USART_TxRxMode) & (USART_TxRxMode_Tx)) > 0){
		/* enabling the transmit complete interrupt */
        Tmp_CR1 |= TCIE_MASK;
    }
    USARTx->CR1  = Tmp_CR1;

    /*clearing TC Flag*/
    USARTx->SR  &= SR_TC_FLAG_CLEAR_MASK;

	/*******************************/
    /* Applying CR2 Configurations */
	/*******************************/
    u16 Tmp_CR2  = ((USARTx->CR2 )&(USARTx_CR2_CLEAR_MASK));
	if (USART_LIN_Mode_Disable == USART_InitStruct->USART_LIN_Mode)
		Tmp_CR2     |= USART_InitStruct->USART_Mode | USART_InitStruct->USART_StopBits;
	else
		Tmp_CR2     |= USART_Mode_Async | USART_StopBits_1 | USART_InitStruct->USART_LIN_Mode | USART_InitStruct->USART_LIN_Interrupt;
    USARTx->CR2  = Tmp_CR2;
    
    /*******************************/
    /* Applying CR3 Configurations */
    /*******************************/
	/* enable DMA transmitter and reciever modes */
    u16 Tmp_CR3  = ((USARTx->CR3 )&(USARTx_CR3_CLEAR_MASK));
    Tmp_CR3     |= USART_InitStruct->USART_DMA_TxRxMode;
    USARTx->CR3  = Tmp_CR3;
	
    /*******************************/
	/* Applying BRR Configurations */
	/*******************************/
    /*  Baud rate values in BRR Configurations  */
    f32 baudrate     = (f32) USART_InitStruct->USART_BaudRate;
    f32 Bus_Clock_Hz = (f32) (Bus_Clock_MHz * 1000000);

    f32 DIV_total    = Bus_Clock_Hz/(16 * baudrate) ;
    u32 DIV_dec      = (u32) DIV_total;
    f32 DIV_frac     = DIV_total - (f32)DIV_dec;
    f32 DIV_frac_16  = DIV_frac * 16;
    u32 DIV_frac_16_rounded;
	
	/* approximating the fraction to the nearest decimal */
    if (DIV_frac_16 > ((u32)DIV_frac_16)+0.49){
    	DIV_frac_16_rounded = ((u32)DIV_frac_16)+1;
    }else{
    	DIV_frac_16_rounded = ((u32)DIV_frac_16);
    }

    u32 BRR       = (DIV_dec<<4)+DIV_frac_16_rounded;
    USARTx->BRR   = (u16)BRR;
}


/* Description: This API shall initialize the paramters     */
/*              of the USART_InitStruct needed by the       */
/*              init function                               */
/* Input  => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
void dUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
    /* inializing a struct needed by the init function
	   with default values                             */
	   
	USART_InitStruct->USART_BaudRate      = 9600;
	USART_InitStruct->USART_StopBits      = USART_StopBits_1;
	USART_InitStruct->USART_Parity        = USART_Parity_No ;
	/* both transmitter and reciever are enabled by default*/
	USART_InitStruct->USART_TxRxMode      = USART_TxRxMode_Rx | USART_TxRxMode_Tx;
	/* both transmitter and reciever are disabled by default*/
	USART_InitStruct->USART_DMA_TxRxMode  = USART_DMA_TxRxMode_Disable;
	/* Asynchronous mode selectred by default */
	USART_InitStruct->USART_Mode          = USART_Mode_Async;
	/* LIN mode disabled by default*/
	USART_InitStruct->USART_LIN_Mode      = USART_LIN_Mode_Disable;
	/* LIN break detection interrupt disabled by default*/
	USART_InitStruct->USART_LIN_Interrupt = USART_LIN_Interrupt_Disable;
}


/* Description: This API shall send one byte of data        */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => Data   {Byte of data to be sent}               */
/* Output => void                                           */
void dUSART_SendByte(USART_typeDef* USARTx,u8 Data){
	/* writing one byte data on the DATA REGISTER */
    USARTx->DR = Data;
}


/* Description: This API shall send one byte of data        */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
u8 dUSART_ReceiveByte(USART_typeDef* USARTx){
	/* reading one byte data on the DATA REGISTER */
    return USARTx->DR;
}


/* Description: This API shall return the status of flags   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_FLAG   {The flag name: USART_FLAG_x}     */
/* Output => void                                           */
FlagStatus_t dUSART_GetFlagStatus(USART_typeDef* USARTx, u16 USART_FLAG){
	FlagStatus_t BitStatus;
	/* reading one bit from STATUS REGISTER  */
    if (((USARTx->SR)&USART_FLAG) == 0){
        BitStatus = Reset;
    }else{
        BitStatus = Set;
    }
    return BitStatus;
}


/* Description: This API shall clear the TC flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
void dUSART_ClearTCFlag(USART_typeDef* USARTx){
    USARTx->SR &= SR_TC_FLAG_CLEAR_MASK;

}

/* Description: This API shall clear the RXNE flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
extern void dUSART_ClearRXNEFlag(USART_typeDef* USARTx){
    USARTx->SR &= SR_RXNE_FLAG_CLEAR_MASK;
}

/* Description: This API shall clear the TC flag            */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/* Output => void                                           */
void dUSART_ClearLBDFlag(USART_typeDef* USARTx){
    USARTx->SR &= SR_LBD_FLAG_CLEAR_MASK;

}

/* Description: This API shall Send LIN break               */
/* Input  => void                                           */
/* Output => void                                           */
void dUSART_SendLIN_Break(USART_typeDef* USARTx){
	USARTx->CR1 |= USARTx_CR1_SBK_Enable ;
}
