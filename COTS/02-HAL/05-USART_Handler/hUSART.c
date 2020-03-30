#include "STD_TYPES.h"
#include <dRCC.h>
#include <dNVIC.h>
#include <dGPIO.h>
#include <hUSART.h>



/*****************************************/
/**************** Defines ****************/
/*****************************************/
#define BUFFER_IDLE      ((u8)0)
#define BUFFER_BUSY      ((u8)1)

/*****************************************/
/************** VARIABLES ****************/
/*****************************************/

u8 flag_habd_txe = 0;



typedef struct
{
u8 * ptrData;
u32  position;
u32  DataSize;
u8   state;
}dataBuffer_t;

typedef struct {
    USART_typeDef* USARTx_x;
    CallBackFn     TxNotify;
    CallBackFn     RxNotify;
    GPIO_t*        GPIO_Tx_map;
    GPIO_t*        GPIO_Rx_map;
    u8             InterruptID;
    dataBuffer_t   Tx_Buffer;
    dataBuffer_t   Rx_Buffer;
    u32            Prephiral_Enable;
    u8             Bus;
}USART_t;

GPIO_t GPIO_UART1_Tx={.GPIO_u16Pin    = GPIO_PIN9_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTA};

GPIO_t GPIO_UART1_Rx={.GPIO_u16Pin    = GPIO_PIN10_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTA};

GPIO_t GPIO_UART2_Tx={.GPIO_u16Pin    = GPIO_PIN2_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTA};

GPIO_t GPIO_UART2_Rx={.GPIO_u16Pin    = GPIO_PIN3_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTA};

GPIO_t GPIO_UART3_Tx={.GPIO_u16Pin    = GPIO_PIN10_MASK,
		              .GPIO_u8PinMode = AlternateFn_10MHz_PUSH_PULL,
				      .GPIO_ptrPort   = GPIO_PORTB};

GPIO_t GPIO_UART3_Rx={.GPIO_u16Pin    = GPIO_PIN11_MASK,
		              .GPIO_u8PinMode = INPUT_PULL_UP_DOWN,
				      .GPIO_ptrPort   = GPIO_PORTB};

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



/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
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


void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
    dUSART_StructDefaultInit(USART_InitStruct);
}


void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct){
	u8 Sys_Freq = RCC_GetSystemClockFreq();
    dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct,Sys_Freq);
}



void hUART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack){
    if (TxCallBack != NULL)
        USARTs[USARTx].TxNotify = TxCallBack;
}

void hUART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack){
    if (RxCallBack != NULL)
        USARTs[USARTx].RxNotify = RxCallBack;
}

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
