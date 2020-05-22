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
#include <dGPIO.h>
#include <dNVIC.h>
#include <dRCC.h>
#include <hUSART.h>
#include <hUSART_Config.h>







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
	/* LIN Break Detection callback functions*/
	CallBackFn     LINNotify;
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
	/* DMA Tx Channel */
	u8             DMA_Tx_Channel;
	/* DMA Rx Channel */
	u8             DMA_Rx_Channel;
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
		.LINNotify = NULL ,
		.GPIO_Tx_map=&GPIO_UART1_Tx,
		.GPIO_Rx_map=&GPIO_UART1_Rx,
		.InterruptID = InterruptID_37,
		.Prephiral_Enable = USART1EN,
		.Bus = APB2,
		.DMA_Tx_Channel = DMA_Channel_4,
		.DMA_Rx_Channel = DMA_Channel_5},

		{.USARTx_x = USARTx_2,
				.TxNotify = NULL ,
				.RxNotify = NULL ,
				.LINNotify = NULL ,
				.GPIO_Tx_map=&GPIO_UART2_Tx,
				.GPIO_Rx_map=&GPIO_UART2_Rx,
				.InterruptID = InterruptID_38,
				.Prephiral_Enable = USART2EN,
				.Bus = APB1,
				.DMA_Tx_Channel = DMA_Channel_6,
				.DMA_Rx_Channel = DMA_Channel_7},


				{.USARTx_x = USARTx_3,
						.TxNotify = NULL ,
						.RxNotify = NULL ,
						.LINNotify = NULL ,
						.GPIO_Tx_map=&GPIO_UART3_Tx,
						.GPIO_Rx_map=&GPIO_UART3_Rx,
						.InterruptID = InterruptID_39,
						.Prephiral_Enable=USART3EN,
						.Bus = APB1,
						.DMA_Tx_Channel = DMA_Channel_2,
						.DMA_Rx_Channel = DMA_Channel_3}};


/* array of DMA configs for each USART */
DMA_InitTypeDef_t DMA_Tx_USARTs []={{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit, 
		.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
		.DMA_CircularMode        = DMA_CircularMode_Disable,
		.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
		.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
		.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
		.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
		.DMA_Direction           = DMA_DirectionMemToPer,
		.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
		.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable},

		{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit,
				.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
				.DMA_CircularMode        = DMA_CircularMode_Disable,
				.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
				.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
				.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
				.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
				.DMA_Direction           = DMA_DirectionMemToPer,
				.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
				.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable},

				{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit,
						.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
						.DMA_CircularMode        = DMA_CircularMode_Disable,
						.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
						.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
						.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
						.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
						.DMA_Direction           = DMA_DirectionMemToPer,
						.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
						.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable}};

/* array of DMA configs for each USART */
DMA_InitTypeDef_t DMA_Rx_USARTs []={{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit, 
		.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
		.DMA_CircularMode        = DMA_CircularMode_Disable,
		.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
		.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
		.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
		.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
		.DMA_Direction           = DMA_DirectionPerToMem,
		.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
		.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable},

		{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit,
				.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
				.DMA_CircularMode        = DMA_CircularMode_Disable,
				.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
				.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
				.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
				.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
				.DMA_Direction           = DMA_DirectionPerToMem,
				.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
				.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable},

				{.DMA_PeripheralDataWidth = DMA_PeripheralDataWidth_8_bit,
						.DMA_MemoryDataWidth     = DMA_MemoryDataWidth_8_bit,
						.DMA_CircularMode        = DMA_CircularMode_Disable,
						.DMA_ChannelPriority     = DMA_ChannelPriority_Low,
						.DMA_Mem2Mem             = DMA_Mem2Mem_Disable,
						.DMA_HalfTransfer        = DMA_HalfTransfer_Disable,
						.DMA_ErrorInterrupt      = DMA_ErrorInterrupt_Disable,
						.DMA_Direction           = DMA_DirectionPerToMem,
						.DMA_PeripheralIncrement = DMA_PeripheralIncrement_Disable,
						.DMA_MemoryIncrement     = DMA_MemoryIncrement_Enable}};


/************************************************************/
/****************** FUNCTION DEFINITIONS ********************/
/************************************************************/


/* Description: This API shall Initialize UART Peripheral   */
/* Input  => u8 {USART1, USART2, .....}         */
/*        => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
void hUSART_Init(u8 USARTx, USART_InitTypeDef* USART_InitStruct){

	/* enabling the USART peripheral using RCC */
	RCC_SetPrephiralClockState(USARTs[USARTx].Bus,USARTs[USARTx].Prephiral_Enable,ON);

	/* getting the Bus clock needed for the Baudrate Calculations */
	u8 Sys_Freq = RCC_GetSystemClockFreq();
	u8 Bus_prescaler = Rcc_GetBusPrescaler(USARTs[USARTx].Bus);
	u8 Bus_Freq_MHz = Sys_Freq/Bus_prescaler;

	/* Seting the Tx and Rx pins mode using GPIO */
	GPIO_voidSetPinMode(USARTs[USARTx].GPIO_Tx_map);
	GPIO_voidSetPinMode(USARTs[USARTx].GPIO_Rx_map);
	/* configuring the Rx pin to be pull up      */
	GPIO_voidSetPinValue(USARTs[USARTx].GPIO_Rx_map->GPIO_ptrPort,USARTs[USARTx].GPIO_Rx_map->GPIO_u16Pin,PULL_UP);

	/* calling the USART driver init */
	dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct,Bus_Freq_MHz);

	/*  enable the interrupt only if the DMA mode is not used */
#if  UART_MODE_DMA == UART_MODE_DMA_Disable
	/* Clear pending flag and enabling the USART interrupt using NVIC */
	NVIC_ClearPendingIRQ(USARTs[USARTx].InterruptID);
	NVIC_EnableIRQ(USARTs[USARTx].InterruptID);
#elif  UART_MODE_DMA == UART_MODE_DMA_Enable
	if (USART_InitStruc->USART_LIN_Interrupt == USART_LIN_Interrupt_Enable) {
		/* Clear pending flag and enabling the USART interrupt using NVIC */
		NVIC_ClearPendingIRQ(USARTs[USARTx].InterruptID);
		NVIC_EnableIRQ(USARTs[USARTx].InterruptID);
	}
	dDMA_Init(USARTs[USARTx].DMA_Tx_Channel, &DMA_Tx_USARTs[USARTx]);
	dDMA_Init(USARTs[USARTx].DMA_Rx_Channel, &DMA_Rx_USARTs[USARTx]);
#endif
}


/* Description: This API shall initialize the paramters     */
/*              of the USART_InitStruct needed by the       */
/*              init function using default values          */
/*              this Api is used only upon initializing     */
/*              with default configurations                 */
/*              O.W. the user shall initialize the struct   */
/*              with the required configurations            */
/* Input  => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
void hUSART_StructDefaultInit(USART_InitTypeDef* USART_InitStruct){
	/* calling the driver default init function */
	dUSART_StructDefaultInit(USART_InitStruct);
}


/* Description: This API shall Configure UART during runtime*/
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => USART_InitTypeDef * {parameters for configs}   */
/* Output => void                                           */
void hUSART_Configure(u8 USARTx, USART_InitTypeDef * USART_InitStruct){
	/* getting the Bus clock needed for the Baudrate Calculations */
	u8 Sys_Freq = RCC_GetSystemClockFreq();
	u8 Bus_prescaler = Rcc_GetBusPrescaler(USARTs[USARTx].Bus);
	u8 Bus_Freq_MHz = Sys_Freq/Bus_prescaler;
	/* calling the driver init function to update the configurations */
	dUSART_Init(USARTs[USARTx].USARTx_x,USART_InitStruct,Bus_Freq_MHz);
}


/* Description: This API shall Configure DMA during runtime*/
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => DMA_InitTypeDef_t * {parameters for configs}   */
/* Output => void                                           */
void hUSART_ConfigureDMA_TxRx_mode(u8 USARTx, DMA_InitTypeDef_t * DMA_USART_Configure , u8 Select){
	switch (Select){
	case Select_Tx:DMA_Tx_USARTs[USARTx] = *DMA_USART_Configure;break;
	case Select_Rx:DMA_Rx_USARTs[USARTx] = *DMA_USART_Configure;break;
	};
}

/* Description: This API shall Set Tx callback Function     */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {TxCallBack}                        */
/* Output => void                                           */
void hUSART_SetTxCallBackFn(u8 USARTx,CallBackFn TxCallBack){
	/* UART DMA mode Disabled */
	if (TxCallBack != NULL)
#if  UART_MODE_DMA == UART_MODE_DMA_Disable
		USARTs[USARTx].TxNotify = TxCallBack;

	/* UART DMA mode Enabled */
#elif UART_MODE_DMA == UART_MODE_DMA_Enable
	dDMA_SetCallBackFn(USARTs[USARTx].DMA_Tx_Channel ,TxCallBack) ;
#endif
}


/* Description: This API shall Send LIN break               */
/* Input  => void                                           */
/* Output => void                                           */
void hUSART_SendLIN_Break(u8 USARTx){
	dUSART_SendLIN_Break(USARTs[USARTx].USARTx_x);
}


/* Description: This API shall Set Rx callback Function     */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {RxCallBack}                        */
/* Output => void                                           */
void hUSART_SetRxCallBackFn(u8 USARTx,CallBackFn RxCallBack){
	/* UART DMA mode Disabled */
	if (RxCallBack != NULL)
#if  UART_MODE_DMA == UART_MODE_DMA_Disable
		USARTs[USARTx].RxNotify = RxCallBack;

	/* UART DMA mode Enabled */
#elif UART_MODE_DMA == UART_MODE_DMA_Enable
	dDMA_SetCallBackFn(USARTs[USARTx].DMA_Rx_Channel ,RxCallBack) ;
#endif
}

/* Description: This API shall Set LIN break detection    
   callback Function                                        */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => CallBackFn {LINCallBack}                       */
/* Output => void                                           */
void hUART_SetLIN_BreakCallBackFn(u8 USARTx,CallBackFn LINCallBack){
	/* UART DMA mode Disabled */
	if (LINCallBack != NULL)
		USARTs[USARTx].LINNotify = LINCallBack;
}


/* Description: This API shall Send an array of Bytes       */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => u8 * Data {pointer to data to be transmitted}  */
/*        => u32 DataLength: number of bytes                */
/* Output => u8 {BUFFER_BUSY , BUFFER_IDLE}                 */
u8 hUSART_Send(u8 USARTx ,u8 * Data ,u32 DataLength ){
	/* UART DMA mode Disabled */
#if  UART_MODE_DMA == UART_MODE_DMA_Disable

	u8 Local_Status = BUFFER_IDLE;
	/* Checking the buffer state to proceed with the Tx request */
	if (USARTs[USARTx].Tx_Buffer.state == BUFFER_IDLE){
		/* initializing the Tx buffer with the data to be transmitted */
		USARTs[USARTx].Tx_Buffer.ptrData  = Data;
		USARTs[USARTx].Tx_Buffer.DataSize = DataLength;
		/* sending the first byte of data */
		dUSART_SendByte(USARTs[USARTx].USARTx_x,USARTs[USARTx].Tx_Buffer.ptrData[USARTs[USARTx].Tx_Buffer.position]);
		//trace_printf("sent frame : %x \n",USARTs[USARTx].Tx_Buffer.ptrData[USARTs[USARTx].Tx_Buffer.position]);
		USARTs[USARTx].Tx_Buffer.position++;
		/* changing the state of the buffer to be busy untill transmitting the required data in the Tx Buffer */
		USARTs[USARTx].Tx_Buffer.state = BUFFER_BUSY;
	}else{
		Local_Status = BUFFER_BUSY;
	}
	return Local_Status;

	/* UART DMA mode Enabled */
#elif UART_MODE_DMA == UART_MODE_DMA_Enable

	DMA_Tx_USARTs[USARTx].DMA_PeripheralBaseAddress = &(USARTs[USARTx].USARTx_x->DR);
	DMA_Tx_USARTs[USARTx].DMA_MemoryBaseAddress     = Data;
	DMA_Tx_USARTs[USARTx].DMA_DataCount             = DataLength;

	dDMA_Configure(USARTs[USARTx].DMA_Tx_Channel,&DMA_Tx_USARTs[USARTx]);
	dDMA_Start(USARTs[USARTx].DMA_Tx_Channel);
	return BUFFER_BUSY;
#endif
}



/* Description: This API shall Recieve an array of Bytes    */
/* Input  => u8 {USART1, USART2, .....}                     */
/*        => u8 * Data {pointer to data to be Recieved}     */
/*        => u32 DataLength: number of bytes                */
/* Output => u8 {BUFFER_BUSY , BUFFER_IDLE}                 */
u8 hUSART_Receive(u8 USARTx ,u8 * Data ,u32 DataLength ){

	/* UART DMA mode Disabled */
#if  UART_MODE_DMA == UART_MODE_DMA_Disable
	u8 Local_Status = BUFFER_IDLE;
	/* Checking the buffer state to proceed with the Tx request */
	if (USARTs[USARTx].Rx_Buffer.state == BUFFER_IDLE){
		/* initializing the Tx buffer with the data to be transmitted */
		USARTs[USARTx].Rx_Buffer.ptrData  = Data;
		USARTs[USARTx].Rx_Buffer.DataSize = DataLength;
		/* changing the state of the buffer to be busy untill transmitting the required data in the Tx Buffer */
		USARTs[USARTx].Rx_Buffer.state = BUFFER_BUSY;
	}else{
		Local_Status = BUFFER_BUSY;
	}
	return Local_Status;

	/* UART DMA mode Enabled */
#elif UART_MODE_DMA == UART_MODE_DMA_Enable

	DMA_Rx_USARTs[USARTx].DMA_PeripheralBaseAddress = &(USARTs[USARTx].USARTx_x->DR);
	DMA_Rx_USARTs[USARTx].DMA_MemoryBaseAddress     = Data;
	DMA_Rx_USARTs[USARTx].DMA_DataCount             = DataLength;

	dDMA_Configure(USARTs[USARTx].DMA_Rx_Channel,&DMA_Rx_USARTs[USARTx]);
	dDMA_Start(USARTs[USARTx].DMA_Rx_Channel);
	return BUFFER_BUSY;
#endif
}



/* Description: Interrupt Request Call Back Function USART1 */
/* Input  => void                                           */
/* Output => void                                           */
void USART1_IRQHandler(void){
	/*************************************************************/
	/*  enable the this part of code if the DMA mode is not used */
	/*  be used when using the handler in sending and recieving  */
	/*************************************************************/

	if (dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_LBD)){
		dUSART_ClearLBDFlag(USARTs[USART1].USARTx_x);
		dUSART_ClearRXNEFlag(USARTs[USART1].USARTx_x);
		/* notifying the application upon break detection*/
		if (USARTs[USART1].LINNotify != NULL){
			USARTs[USART1].LINNotify();
		}
	}

#if   UART_MODE_DMA == UART_MODE_DMA_Disable

	/* RXNE FLAG: Receive data Register not empty Flag */

	/* checking that the interrupt trigger is the RXNE flag */
	u8 Local_RXNE_Flag = dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_RXNE);
	if (Set == Local_RXNE_Flag){
		/*checking if the buffer is still not empty */
		if (USARTs[USART1].Rx_Buffer.state == BUFFER_BUSY){
			/* Recieve the next byte of data */
			USARTs[USART1].Rx_Buffer.ptrData[USARTs[USART1].Rx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART1].USARTx_x);

			//trace_printf("received value : %x  \n",USARTs[USART1].Rx_Buffer.ptrData[USARTs[USART1].Rx_Buffer.position]);

			USARTs[USART1].Rx_Buffer.position++;

			/* checking if the data is fully Recieved successfully */
			if (USARTs[USART1].Rx_Buffer.position == USARTs[USART1].Rx_Buffer.DataSize){
				/* Reseting the Rx Buffer */
				USARTs[USART1].Rx_Buffer.position = 0;
				USARTs[USART1].Rx_Buffer.ptrData  = NULL;
				USARTs[USART1].Rx_Buffer.DataSize = 0;
				USARTs[USART1].Rx_Buffer.state    = BUFFER_IDLE;
				/* notifying the application upon Reception completion*/
				if(USARTs[USART1].RxNotify != NULL){
					USARTs[USART1].RxNotify();
				}
			}
		}
	}
	/* TC FLAG: Transmission Complete Flag */

	/* Clearing the TC flag at the first interrupt */
	if(USARTs[USART1].Tx_Buffer.position == 0){
		dUSART_ClearTCFlag(USARTs[USART1].USARTx_x);
	}

	/* checking that the interrupt trigger is the TC flag */
	if (dUSART_GetFlagStatus(USARTs[USART1].USARTx_x,USART_FLAG_TC)){
		/* checking if the data is fully transmitted successfully */
		if (USARTs[USART1].Tx_Buffer.position == USARTs[USART1].Tx_Buffer.DataSize){
			/* Reseting the Tx Buffer */
			USARTs[USART1].Tx_Buffer.position = 0;
			USARTs[USART1].Tx_Buffer.ptrData  = NULL;
			USARTs[USART1].Tx_Buffer.DataSize = 0;
			USARTs[USART1].Tx_Buffer.state    = BUFFER_IDLE;
			/* notifying the application upon transmission completion*/
			if (USARTs[USART1].TxNotify != NULL){
				USARTs[USART1].TxNotify();
			}

			/*checking if the buffer is still not empty */
		}else if (USARTs[USART1].Tx_Buffer.state == BUFFER_BUSY){
			/* send the next byte of data */
			dUSART_SendByte(USARTs[USART1].USARTx_x,USARTs[USART1].Tx_Buffer.ptrData[USARTs[USART1].Tx_Buffer.position]);
			//trace_printf("sent frame : %x \n",USARTs[USART1].Tx_Buffer.ptrData[USARTs[USART1].Tx_Buffer.position]);
			USARTs[USART1].Tx_Buffer.position++;
		}

	}

#endif

}

/* Description: Interrupt Request Call Back Function USART2 */
/* Input  => void                                           */
/* Output => void                                           */
void USART2_IRQHandler(void){
	/*************************************************************/
	/*  enable the this part of code if the DMA mode is not used */
	/*  be used when using the handler in sending and recieving  */
	/*************************************************************/

	if (dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_LBD)){
		dUSART_ClearLBDFlag(USARTs[USART2].USARTx_x);
		dUSART_ClearRXNEFlag(USARTs[USART2].USARTx_x);
		/* notifying the application upon break detection*/
		if (USARTs[USART2].LINNotify != NULL){
			USARTs[USART2].LINNotify();
		}
	}

#if   UART_MODE_DMA == UART_MODE_DMA_Disable

	/* RXNE FLAG: Receive data Register not empty Flag */

	/* checking that the interrupt trigger is the RXNE flag */
	u8 Local_RXNE_Flag = dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_RXNE);
	if (Set == Local_RXNE_Flag){
		/*checking if the buffer is still not empty */
		if (USARTs[USART2].Rx_Buffer.state == BUFFER_BUSY){
			/* Recieve the next byte of data */
			USARTs[USART2].Rx_Buffer.ptrData[USARTs[USART2].Rx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART2].USARTx_x);

			//trace_printf("received value : %x  \n",USARTs[USART2].Rx_Buffer.ptrData[USARTs[USART2].Rx_Buffer.position]);

			USARTs[USART2].Rx_Buffer.position++;

			/* checking if the data is fully Recieved successfully */
			if (USARTs[USART2].Rx_Buffer.position == USARTs[USART2].Rx_Buffer.DataSize){
				/* Reseting the Rx Buffer */
				USARTs[USART2].Rx_Buffer.position = 0;
				USARTs[USART2].Rx_Buffer.ptrData  = NULL;
				USARTs[USART2].Rx_Buffer.DataSize = 0;
				USARTs[USART2].Rx_Buffer.state    = BUFFER_IDLE;
				/* notifying the application upon Reception completion*/
				if(USARTs[USART2].RxNotify != NULL){
					USARTs[USART2].RxNotify();
				}
			}
		}
	}
	/* TC FLAG: Transmission Complete Flag */

	/* Clearing the TC flag at the first interrupt */
	if(USARTs[USART2].Tx_Buffer.position == 0){
		dUSART_ClearTCFlag(USARTs[USART2].USARTx_x);
	}

	/* checking that the interrupt trigger is the TC flag */
	if (dUSART_GetFlagStatus(USARTs[USART2].USARTx_x,USART_FLAG_TC)){
		/* checking if the data is fully transmitted successfully */
		if (USARTs[USART2].Tx_Buffer.position == USARTs[USART2].Tx_Buffer.DataSize){
			/* Reseting the Tx Buffer */
			USARTs[USART2].Tx_Buffer.position = 0;
			USARTs[USART2].Tx_Buffer.ptrData  = NULL;
			USARTs[USART2].Tx_Buffer.DataSize = 0;
			USARTs[USART2].Tx_Buffer.state    = BUFFER_IDLE;
			/* notifying the application upon transmission completion*/
			if (USARTs[USART2].TxNotify != NULL){
				USARTs[USART2].TxNotify();
			}

			/*checking if the buffer is still not empty */
		}else if (USARTs[USART2].Tx_Buffer.state == BUFFER_BUSY){
			/* send the next byte of data */
			dUSART_SendByte(USARTs[USART2].USARTx_x,USARTs[USART2].Tx_Buffer.ptrData[USARTs[USART2].Tx_Buffer.position]);
			//trace_printf("sent frame : %x \n",USARTs[USART2].Tx_Buffer.ptrData[USARTs[USART2].Tx_Buffer.position]);
			USARTs[USART2].Tx_Buffer.position++;
		}

	}

#endif

}


/* Description: Interrupt Request Call Back Function USART3 */
/* Input  => void                                           */
/* Output => void                                           */
void USART3_IRQHandler(void){
	/*************************************************************/
	/*  enable the this part of code if the DMA mode is not used */
	/*  be used when using the handler in sending and recieving  */
	/*************************************************************/

	if (dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_LBD)){
		dUSART_ClearLBDFlag(USARTs[USART3].USARTx_x);
		dUSART_ClearRXNEFlag(USARTs[USART3].USARTx_x);
		/* notifying the application upon break detection*/
		if (USARTs[USART3].LINNotify != NULL){
			USARTs[USART3].LINNotify();
		}
	}

#if   UART_MODE_DMA == UART_MODE_DMA_Disable

	/* RXNE FLAG: Receive data Register not empty Flag */

	/* checking that the interrupt trigger is the RXNE flag */
	u8 Local_RXNE_Flag = dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_RXNE);
	if (Set == Local_RXNE_Flag){
		/*checking if the buffer is still not empty */
		if (USARTs[USART3].Rx_Buffer.state == BUFFER_BUSY){
			/* Recieve the next byte of data */
			USARTs[USART3].Rx_Buffer.ptrData[USARTs[USART3].Rx_Buffer.position] = dUSART_ReceiveByte(USARTs[USART3].USARTx_x);

			//trace_printf("received value : %x  \n",USARTs[USART3].Rx_Buffer.ptrData[USARTs[USART3].Rx_Buffer.position]);

			USARTs[USART3].Rx_Buffer.position++;

			/* checking if the data is fully Recieved successfully */
			if (USARTs[USART3].Rx_Buffer.position == USARTs[USART3].Rx_Buffer.DataSize){
				/* Reseting the Rx Buffer */
				USARTs[USART3].Rx_Buffer.position = 0;
				USARTs[USART3].Rx_Buffer.ptrData  = NULL;
				USARTs[USART3].Rx_Buffer.DataSize = 0;
				USARTs[USART3].Rx_Buffer.state    = BUFFER_IDLE;
				/* notifying the application upon Reception completion*/
				if(USARTs[USART3].RxNotify != NULL){
					USARTs[USART3].RxNotify();
				}
			}
		}
	}
	/* TC FLAG: Transmission Complete Flag */

	/* Clearing the TC flag at the first interrupt */
	if(USARTs[USART3].Tx_Buffer.position == 0){
		dUSART_ClearTCFlag(USARTs[USART3].USARTx_x);
	}

	/* checking that the interrupt trigger is the TC flag */
	if (dUSART_GetFlagStatus(USARTs[USART3].USARTx_x,USART_FLAG_TC)){
		/* checking if the data is fully transmitted successfully */
		if (USARTs[USART3].Tx_Buffer.position == USARTs[USART3].Tx_Buffer.DataSize){
			/* Reseting the Tx Buffer */
			USARTs[USART3].Tx_Buffer.position = 0;
			USARTs[USART3].Tx_Buffer.ptrData  = NULL;
			USARTs[USART3].Tx_Buffer.DataSize = 0;
			USARTs[USART3].Tx_Buffer.state    = BUFFER_IDLE;
			/* notifying the application upon transmission completion*/
			if (USARTs[USART3].TxNotify != NULL){
				USARTs[USART3].TxNotify();
			}

			/*checking if the buffer is still not empty */
		}else if (USARTs[USART3].Tx_Buffer.state == BUFFER_BUSY){
			/* send the next byte of data */
			dUSART_SendByte(USARTs[USART3].USARTx_x,USARTs[USART3].Tx_Buffer.ptrData[USARTs[USART3].Tx_Buffer.position]);
			//trace_printf("sent frame : %x \n",USARTs[USART3].Tx_Buffer.ptrData[USARTs[USART3].Tx_Buffer.position]);
			USARTs[USART3].Tx_Buffer.position++;
		}

	}

#endif

}

