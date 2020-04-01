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

#include "STD_TYPES.h"
#include <dRCC.h>
#include <dNVIC.h>
#include <dGPIO.h>
#include <hUSART.h>

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define BUFFER_IDLE      ((u8)0)
#define BUFFER_BUSY      ((u8)1)

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef struct
{
u8 * ptrData;
u32  position;
u32  DataSize;
/* state is busy (upon sending or recieving data) or idle*/
u8   state;
}dataBuffer_t;

typedef struct {
	/* the USART struct for the register address*/
    USART_typeDef* USARTx_x;
	/* the transmitter  callback functions*/
    CallBackFn     TxNotify;
	/* the Reciever  callback functions*/
    CallBackFn     RxNotify;
	/* the Transmitter  GPIO pin Configs*/
    GPIO_t*        GPIO_Tx_map;
	/* the Reciever  GPIO pin Configs*/
    GPIO_t*        GPIO_Rx_map;
	/* Interrupt ID for each USART peripheral */
    u8             InterruptID;
	/* data buffer for the data to be transmitted*/
    dataBuffer_t   Tx_Buffer;
	/* data buffer for the data to be Recieved*/
    dataBuffer_t   Rx_Buffer;
	/* Mask for the Peripheral enable using RCC */
    u32            Prephiral_Enable;
	/* The Bus on which the USART is clocked by */
    u8             Bus;
	
}USART_t;

/************************************************************/
/****************** VARIABLES DEFINITIONS ******************/
/************************************************************/

/* initializing the GPIO configiration for UART1 Transmitter pin */
GPIO_t GPIO_UART1_Tx={.GPIO_u16Pin    = GPIO_PIN9_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTA};

/* initializing the GPIO configiration for UART1 Reciever pin */
GPIO_t GPIO_UART1_Rx={.GPIO_u16Pin    = GPIO_PIN10_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTA};

/* initializing the GPIO configiration for UART2 Transmitter pin */
GPIO_t GPIO_UART2_Tx={.GPIO_u16Pin    = GPIO_PIN2_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTA};

/* initializing the GPIO configiration for UART2 Reciever pin */
GPIO_t GPIO_UART2_Rx={.GPIO_u16Pin    = GPIO_PIN3_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTA};

/* initializing the GPIO configiration for UART3 Transmitter pin */
GPIO_t GPIO_UART3_Tx={.GPIO_u16Pin    = GPIO_PIN10_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTB};

/* initializing the GPIO configiration for UART3 Reciever pin */
GPIO_t GPIO_UART3_Rx={.GPIO_u16Pin    = GPIO_PIN11_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTB};

/* an array of UART_t struct which holds the UARTx (USART Peripheral number), callback Functions 
   GPIO Pins configiration and the interruptID for each UART                                     */
USART_t USARTs[] ={{.USARTx_x = USARTx_1,
		            .TxNotify = NULL ,
					.RxNotify = NULL ,
		            .GPIO_Tx_map=&GPIO_UART1_Tx,
					.GPIO_Rx_map=&GPIO_UART1_Rx,
                    .InterruptID = InterruptID_37,
					.Prephiral_Enable = USART1EN,
                    .Bus = APB2},

                   {.USARTx_x = USARTx_2,
                    .TxNotify = NULL ,
					.RxNotify = NULL ,
		            .GPIO_Tx_map=&GPIO_UART2_Tx,
					.GPIO_Rx_map=&GPIO_UART2_Rx,
                    .InterruptID = InterruptID_38,
					.Prephiral_Enable = USART2EN,
                    .Bus = APB1},


                   {.USARTx_x = USARTx_3,
                    .TxNotify = NULL ,
					.RxNotify = NULL ,
		            .GPIO_Tx_map=&GPIO_UART3_Tx,
					.GPIO_Rx_map=&GPIO_UART3_Rx,
                    .InterruptID = InterruptID_39,
					.Prephiral_Enable=USART3EN,
                    .Bus = APB1}};

/************************************************************/
/****************** FUNCTION DEFINITIONS *******************/
/************************************************************/


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void hUSART_Init(u8 USARTx, USART_InitTypeDef* USART_InitStruct){

    RCC_SetPrephiralClockState(USARTs[USARTx].Bus,USARTs[USARTx].Prephiral_Enable,ON);

    u8 Sys_Freq = RCC_GetSystemClockFreq();
    u8 Bus_prescaler = Rcc_GetBusPrescaler(USARTs[USARTx].Bus);
    u8 Bus_Freq_MHz = Sys_Freq/Bus_prescaler;
    GPIO_voidSetPinMode(USARTs[USARTx].GPIO_Tx_map);
    GPIO_voidSetPinMode(USARTs[USARTx].GPIO_Rx_map);
    GPIO_voidSetPinValue(USARTs[USARTx].GPIO_Rx_map->GPIO_ptrPort,USARTs[USARTx].GPIO_Rx_map->GPIO_u16Pin,PULL_UP);

    dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct,Bus_Freq_MHz);

    NVIC_ClearPendingIRQ(USARTs[USARTx].InterruptID);
    NVIC_EnableIRQ(USARTs[USARTx].InterruptID);
}


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
    dUSART_StructDefaultInit(USART_InitStruct);
}


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct){
	u8 Sys_Freq = RCC_GetSystemClockFreq();
    dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct,Sys_Freq);
}



/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void hUART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack){
    if (TxCallBack != NULL)
        USARTs[USARTx].TxNotify = TxCallBack;
}


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void hUART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack){
    if (RxCallBack != NULL)
        USARTs[USARTx].RxNotify = RxCallBack;
}


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
u8 hUSART_Send(u8 USARTx ,u8 * Data ,u32 DataLength ){
    u8 Local_Status = BUFFER_IDLE;
    if (USARTs[USARTx].Tx_Buffer.state == BUFFER_IDLE){
        USARTs[USARTx].Tx_Buffer.ptrData  = Data;
        USARTs[USARTx].Tx_Buffer.DataSize = DataLength;
        dUSART_SendByte(USARTs[USARTx].USARTx_x,USARTs[USARTx].Tx_Buffer.ptrData[USARTs[USARTx].Tx_Buffer.position]);
        USARTs[USARTx].Tx_Buffer.position++;
        USARTs[USARTx].Tx_Buffer.state = BUFFER_BUSY;
    }else{
        Local_Status = BUFFER_BUSY;
    }
    return Local_Status;
}



/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
u8 hUSART_Receive(u8 USARTx ,u8 * Data ,u32 DataLength ){
    u8 Local_Status = BUFFER_IDLE;
    if (USARTs[USARTx].Rx_Buffer.state == BUFFER_IDLE){
        USARTs[USARTx].Rx_Buffer.ptrData  = Data;
        USARTs[USARTx].Rx_Buffer.DataSize = DataLength;
        USARTs[USARTx].Rx_Buffer.state = BUFFER_BUSY;
    }else{
        Local_Status = BUFFER_BUSY;
    }
    return Local_Status;
}



/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void USART1_IRQHandler(void){
	if(USARTs[USART1].Tx_Buffer.position == 0){
        dUSART_ClearTCFlag(USARTs[USART1].USARTx_x);
	}


    if (dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_TC)){
        if (USARTs[USART1].Tx_Buffer.position == USARTs[USART1].Tx_Buffer.DataSize){
            USARTs[USART1].Tx_Buffer.position = 0;
            USARTs[USART1].Tx_Buffer.ptrData  = NULL;
            USARTs[USART1].Tx_Buffer.DataSize = 0;
            USARTs[USART1].Tx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART1].TxNotify();
        }else if (USARTs[USART1].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART1].USARTx_x,USARTs[USART1].Tx_Buffer.ptrData[USARTs[USART1].Tx_Buffer.position]);
            USARTs[USART1].Tx_Buffer.position++;
        }

    }

    u8 Local_RXNE_Flag = dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_RXNE);
    if (Set == Local_RXNE_Flag){

        if (USARTs[USART1].Rx_Buffer.state == BUFFER_BUSY){
            USARTs[USART1].Rx_Buffer.ptrData[USARTs[USART1].Rx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART1].USARTx_x);

            USARTs[USART1].Rx_Buffer.position++;

          if (USARTs[USART1].Rx_Buffer.position == USARTs[USART1].Rx_Buffer.DataSize){
            USARTs[USART1].Rx_Buffer.position = 0;
            USARTs[USART1].Rx_Buffer.ptrData  = NULL;
            USARTs[USART1].Rx_Buffer.DataSize = 0;
            USARTs[USART1].Rx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART1].RxNotify();
          }
        }
    }
}

/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void USART2_IRQHandler(void){
    if (dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_TC)){
        if (USARTs[USART2].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART2].USARTx_x,USARTs[USART2].Tx_Buffer.ptrData[USARTs[USART2].Tx_Buffer.position]);
            USARTs[USART2].Tx_Buffer.position++;
        }
        if (USARTs[USART2].Tx_Buffer.position == USARTs[USART2].Tx_Buffer.DataSize){
            USARTs[USART2].Tx_Buffer.position = 0;
            USARTs[USART2].Tx_Buffer.ptrData  = NULL;
            USARTs[USART2].Tx_Buffer.DataSize = 0;
            USARTs[USART2].Tx_Buffer.state    = BUFFER_IDLE;
            dUSART_ClearTCFlag(USARTs[USART2].USARTx_x);
            USARTs[USART2].TxNotify();
        }
    }
    if (dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_RXNE)){
        if (USARTs[USART2].Rx_Buffer.state == BUFFER_BUSY){
            USARTs[USART2].Rx_Buffer.ptrData[USARTs[USART2].Tx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART2].USARTx_x);
            USARTs[USART2].Rx_Buffer.position++;
        }
        if (USARTs[USART2].Rx_Buffer.position == USARTs[USART2].Rx_Buffer.DataSize){
            USARTs[USART2].Rx_Buffer.position = 0;
            USARTs[USART2].Rx_Buffer.ptrData  = NULL;
            USARTs[USART2].Rx_Buffer.DataSize = 0;
            USARTs[USART2].Rx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART2].RxNotify();
        }
    }
}


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => USART_typeDef* {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/*        => Sys_Freq: Input frequency to the peripheral    */
/* Output => void                                           */
void USART3_IRQHandler(void){
    if (dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_TC)){
        if (USARTs[USART3].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART3].USARTx_x,USARTs[USART3].Tx_Buffer.ptrData[USARTs[USART3].Tx_Buffer.position]);
            USARTs[USART3].Tx_Buffer.position++;
        }
        if (USARTs[USART3].Tx_Buffer.position == USARTs[USART3].Tx_Buffer.DataSize){
            USARTs[USART3].Tx_Buffer.position = 0;
            USARTs[USART3].Tx_Buffer.ptrData  = NULL;
            USARTs[USART3].Tx_Buffer.DataSize = 0;
            USARTs[USART3].Tx_Buffer.state    = BUFFER_IDLE;
            dUSART_ClearTCFlag(USARTs[USART3].USARTx_x);
            USARTs[USART3].TxNotify();
        }
    }
    if (dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_RXNE)){
        if (USARTs[USART3].Rx_Buffer.state == BUFFER_BUSY){
            USARTs[USART3].Rx_Buffer.ptrData[USARTs[USART3].Tx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART3].USARTx_x);
            USARTs[USART3].Rx_Buffer.position++;
        }
        if (USARTs[USART3].Rx_Buffer.position == USARTs[USART3].Rx_Buffer.DataSize){
            USARTs[USART3].Rx_Buffer.position = 0;
            USARTs[USART3].Rx_Buffer.ptrData  = NULL;
            USARTs[USART3].Rx_Buffer.DataSize = 0;
            USARTs[USART3].Rx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART3].RxNotify();
        }
    }
}
