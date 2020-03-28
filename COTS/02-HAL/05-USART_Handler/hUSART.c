#include "STD_TYPES.h"
#include "hUSART.h"
#include "dUSART.h"
#include "dGPIO.h"
#include "dNVIC.h"


/*****************************************/
/**************** Defines ****************/
/*****************************************/
#define BUFFER_IDLE      ((u8)0)
#define BUFFER_BUSY      ((u8)1)

/*****************************************/
/************** VARIABLES ****************/
/*****************************************/



typedef void (*CallBackFn)void;
CallBackFn TxNotify();
CallBackFn RxNotify();

typedef struct
{
u8 * ptrData;
u32  position;
u32  DataSize;
u8   state;
}dataBuffer_t;

typedef struct {
    USART_TypeDef* USARTx_x;
    CallBackFn     TxNotify;
    CallBackFn     RxNotify;
    GPIO_t*        GPIO_map;
    u8             InterruptID;
    dataBuffer_t   Tx_Buffer;
    dataBuffer_t   Rx_Buffer;
}USART_t;



USART_t USARTs[] ={{.USARTx_x = USARTx_1, .TxNotify = NULL , .RxNotify = NULL ,
                    .GPIO_map->GPIO_u16Pin  = GPIO_PIN9_MASK | GPIO_PIN10_MASK,
                    .GPIO_map->GPIO_ptrPort = GPIO_PORTA,
                    .GPIO_map->GPIO_ptrPort = AlternateFn_10MHz_PUSH_PULL,
                    .InterruptID = InterruptID_37},

                   {.USARTx_x = USARTx_2, .TxNotify = NULL , .RxNotify = NULL ,
                    .GPIO_map->GPIO_u16Pin  = GPIO_PIN2_MASK | GPIO_PIN3_MASK,
                    .GPIO_map->GPIO_ptrPort = GPIO_PORTA,
                    .GPIO_map->GPIO_ptrPort = AlternateFn_10MHz_PUSH_PULL,
                    .InterruptID = InterruptID_38},

                   {.USARTx_x = USARTx_3, .TxNotify = NULL , .RxNotify = NULL ,
                    .GPIO_map->GPIO_u16Pin  = GPIO_PIN10_MASK | GPIO_PIN11_MASK,
                    .GPIO_map->GPIO_ptrPort = GPIO_PORTB,
                    .GPIO_map->GPIO_ptrPort = AlternateFn_10MHz_PUSH_PULL,
                    .InterruptID = InterruptID_39}}};



/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
void hUSART_Init(u8 USARTx, USART_InitTypeDef* USART_InitStruct){
    GPIO_voidSetPinMode(USARTs[USARTx].GPIO_map);
    dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct);
    NVIC_ClearPendingIRQ(USARTs[USARTx].InterruptID);
    NVIC_EnableIRQ(USARTs[USARTx].InterruptID);
}


void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
    dUSART_StructDefaultInit(USART_InitStruct);
}


void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct){
    dUSART_Init(USARTs[USARTx],USART_InitStruct);
}



void hUART_SetTxCallBackFn(u8 USARTx,void(*TxCallBack)(void)){
    if (TxCallBack != NULL)
        USARTs[USARTx].TxNotify = TxCallBack;
}

void hUART_SetRxCallBackFn(u8 USARTx,void(*RxCallBack)(void)){
    if (RxCallBack != NULL)
        USARTs[USARTx].RxNotify = RxCallBack;
}

u8 hUSART_Send(u8 USARTx,u8 * Data , u32 DataLength){
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


u8 hUSART_Receive(u8 USARTx,u8 * Data , u32 DataLength){
    u8 Local_Status = BUFFER_IDLE;
    if (USARTs[USARTx].Rx_Buffer.state == BUFFER_IDLE){
        USARTs[USARTx].Rx_Buffer.ptrData  = Data;
        USARTs[USARTx].Rx_Buffer.DataSize = DataLength;
        dUSART_SendByte(USARTs[USARTx].USARTx_x,USARTs[USARTx].Tx_Buffer.ptrData[USARTs[USARTx].Tx_Buffer.position]);
        USARTs[USARTx].Rx_Buffer.position++;
        USARTs[USARTx].Rx_Buffer.state = BUFFER_BUSY;
    }else{
        Local_Status = BUFFER_BUSY;
    }
    return Local_Status;
}


USART1_IRQHandler(void){
    if (dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_TXE)){
        if (USARTs[USART1].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART1].USARTx_x,USARTs[USART1].Tx_Buffer.ptrData[USARTs[USART1].Tx_Buffer.position]);
            USARTs[USART1].Tx_Buffer.position++;
        }
        if (USARTs[USART1].Tx_Buffer.position == USARTs[USART1].Tx_Buffer.DataSize){
            USARTs[USART1].Tx_Buffer.position = 0;
            USARTs[USART1].Tx_Buffer.ptrData  = NULL;
            USARTs[USART1].Tx_Buffer.DataSize = 0;
            USARTs[USART1].Tx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART1].TxNotify();
        }
    }
    if (dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_RXNE)){
        if (USARTs[USART1].Rx_Buffer.state == BUFFER_BUSY){
            USARTs[USART1].Rx_Buffer.ptrData[USARTs[USART1].Tx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART1].USARTx_x);
            USARTs[USART1].Rx_Buffer.position++;
        }
        if (USARTs[USART1].Rx_Buffer.position == USARTs[USART1].Rx_Buffer.DataSize){
            USARTs[USART1].Rx_Buffer.position = 0;
            USARTs[USART1].Rx_Buffer.ptrData  = NULL;
            USARTs[USART1].Rx_Buffer.DataSize = 0;
            USARTs[USART1].Rx_Buffer.state    = BUFFER_IDLE;
            USARTs[USART1].RxNotify();
        }
    }
}

USART2_IRQHandler(void){
    if (dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_TXE)){
        if (USARTs[USART2].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART2].USARTx_x,USARTs[USART2].Tx_Buffer.ptrData[USARTs[USART2].Tx_Buffer.position]);
            USARTs[USART2].Tx_Buffer.position++;
        }
        if (USARTs[USART2].Tx_Buffer.position == USARTs[USART2].Tx_Buffer.DataSize){
            USARTs[USART2].Tx_Buffer.position = 0;
            USARTs[USART2].Tx_Buffer.ptrData  = NULL;
            USARTs[USART2].Tx_Buffer.DataSize = 0;
            USARTs[USART2].Tx_Buffer.state    = BUFFER_IDLE;
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

USART3_IRQHandler(void){
    if (dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_TXE)){
        if (USARTs[USART3].Tx_Buffer.state == BUFFER_BUSY){
            dUSART_SendByte(USARTs[USART3].USARTx_x,USARTs[USART3].Tx_Buffer.ptrData[USARTs[USART3].Tx_Buffer.position]);
            USARTs[USART3].Tx_Buffer.position++;
        }
        if (USARTs[USART3].Tx_Buffer.position == USARTs[USART3].Tx_Buffer.DataSize){
            USARTs[USART3].Tx_Buffer.position = 0;
            USARTs[USART3].Tx_Buffer.ptrData  = NULL;
            USARTs[USART3].Tx_Buffer.DataSize = 0;
            USARTs[USART3].Tx_Buffer.state    = BUFFER_IDLE;
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
