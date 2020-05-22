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
#include <dDMA.h>
#include <dNVIC.h>





/************************************************************/
/************************** MACROS **************************/
/************************************************************/
#define DMA_BASE_ADDRESS	                             ((u32)0x40020000)
#define DMA 			                                 ((volatile DMA_Type*)(DMA_BASE_ADDRESS))

#define CCR_CLEAR_MASK                                   ((u32)0x00000000)
#define DMA_TC_InterruptEnable                           ((u32)0x00000002)

#define DMA_Channelx_Enable                              ((u32)0x00000001)
#define DMA_Channelx_Disable                             ((u32)0xFFFFFFFE)

#define DMA_ch1_InterruptFlag_ClearMask                  ((u32)0x0000000F)
#define DMA_ch2_InterruptFlag_ClearMask                  ((u32)0x000000F0)
#define DMA_ch3_InterruptFlag_ClearMask                  ((u32)0x00000F00)
#define DMA_ch4_InterruptFlag_ClearMask                  ((u32)0x0000F000)
#define DMA_ch5_InterruptFlag_ClearMask                  ((u32)0x000F0000)
#define DMA_ch6_InterruptFlag_ClearMask                  ((u32)0x00F00000)
#define DMA_ch7_InterruptFlag_ClearMask                  ((u32)0x0F000000)

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/
typedef struct
{
	u32 CCR;
	u32 CNDTR;
	u32 CPAR;
	u32 CMAR;
	u32 Reserved;
}DMA_Channel;

typedef struct 
{
	u32 ISR;
	u32 IFCR ;
	DMA_Channel Channel[7];
}DMA_Type;

/************************************************************/
/************************* VARIABLES ************************/
/************************************************************/

static const u8 DMA_InterruptIDs[7] = {InterruptID_11,
                                       InterruptID_12,
                                       InterruptID_13,
                                       InterruptID_14,
                                       InterruptID_15,
                                       InterruptID_16,
                                       InterruptID_17 };
									   

static DMA_CallBackFn DMA_CallBacks[7] = {};

/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/



void dDMA_Init( u8 DMA_Channel, DMA_InitTypeDef_t * DMA_InitStruct){

	/* Copy configuration register into a temp variable */
	u32 tempReg = DMA->Channel[DMA_Channel].CCR;
	
	/* Clearing the tempReg */
	tempReg    &= CCR_CLEAR_MASK;
	
	/* setting DMA configurations */
	tempReg    |= (DMA_InitStruct->DMA_Direction       | DMA_InitStruct->DMA_PeripheralIncrement |
                   DMA_InitStruct->DMA_MemoryIncrement | DMA_InitStruct->DMA_PeripheralDataWidth |
                   DMA_InitStruct->DMA_MemoryDataWidth | DMA_InitStruct->DMA_CircularMode        |
                   DMA_InitStruct->DMA_ChannelPriority | DMA_InitStruct->DMA_Mem2Mem               ) ;

	/* enable DMA Interrupts */
	tempReg    |= (DMA_InitStruct->DMA_HalfTransfer       |
	               DMA_InitStruct->DMA_ErrorInterrupt     |
				   DMA_TC_InterruptEnable                   );

    /* copy tempReg Value to the CRR Register */
	DMA->Channel[DMA_Channel].CCR   = tempReg;

	/* setting data counter value */
	DMA->Channel[DMA_Channel].CNDTR = ((u16)DMA_InitStruct->DMA_DataCount);

	/* setting Memory Address */
	DMA->Channel[DMA_Channel].CMAR  = DMA_InitStruct->DMA_MemoryBaseAddress;

	/* setting Peripheral Address */
	DMA->Channel[DMA_Channel].CPAR  = DMA_InitStruct->DMA_PeripheralBaseAddress;

	/* Clear pending flag and enabling the USART interrupt using NVIC */
    NVIC_ClearPendingIRQ(DMA_InterruptIDs[DMA_Channel]);
    NVIC_EnableIRQ(DMA_InterruptIDs[DMA_Channel]);

}


void dDMA_GetCurrentDataCounter(u8 DMA_Channel, u16 * CurrentDataCounter){
	*CurrentDataCounter = (u16)(DMA->Channel[DMA_Channel].CNDTR);
}

void dDMA_Start(u8 DMA_Channel){

	/* clearing the Enable for DMA */
		DMA->Channel[DMA_Channel].CCR &= DMA_Channelx_Disable;
	/* sets the enable bit for channelx */
		DMA->Channel[DMA_Channel].CCR |= DMA_Channelx_Enable;
}

void dDMA_Configure(u8 DMA_Channel, DMA_InitTypeDef_t * DMA_InitStruct){
	
	/* Copy configuration register into a temp variable */
	u32 tempReg = DMA->Channel[DMA_Channel].CCR;
	
	/* Clearing the tempReg */
	tempReg    &= CCR_CLEAR_MASK;
	
	/* setting DMA configurations */
	tempReg    |= (DMA_InitStruct->DMA_Direction       | DMA_InitStruct->DMA_PeripheralIncrement |
                   DMA_InitStruct->DMA_MemoryIncrement | DMA_InitStruct->DMA_PeripheralDataWidth |
                   DMA_InitStruct->DMA_MemoryDataWidth | DMA_InitStruct->DMA_CircularMode        |
                   DMA_InitStruct->DMA_ChannelPriority | DMA_InitStruct->DMA_Mem2Mem               ) ;

	/* enable DMA Interrupts */
	tempReg    |= (DMA_InitStruct->DMA_HalfTransfer       |
	               DMA_InitStruct->DMA_ErrorInterrupt     |
				   DMA_TC_InterruptEnable                  );

    /* copy tempReg Value to the CRR Register */
	DMA->Channel[DMA_Channel].CCR   = tempReg;

	/* setting data counter value */
	DMA->Channel[DMA_Channel].CNDTR = ((u16)DMA_InitStruct->DMA_DataCount);

	/* setting Memory Address */
	DMA->Channel[DMA_Channel].CMAR  = DMA_InitStruct->DMA_MemoryBaseAddress;

	/* setting Peripheral Address */
	DMA->Channel[DMA_Channel].CPAR  = DMA_InitStruct->DMA_PeripheralBaseAddress;
	
}

/* DMA set interrput call back */
void dDMA_SetCallBackFn(u8 DMA_Channel , DMA_CallBackFn DMA_CallBack){
	DMA_CallBacks[DMA_Channel] = DMA_CallBack;
}


/* DMA channel1 interrupt handler */
void DMA1_Channel1_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR &= DMA_ch1_InterruptFlag_ClearMask; 
	/* calling the call back function */
	if (DMA_CallBacks[0] != NULL){
		DMA_CallBacks[0]();
	}
}
/* DMA channel2 interrupt handler */
void DMA1_Channel2_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch2_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[1] != NULL){
		DMA_CallBacks[1]();
	}
}
/* DMA channel3 interrupt handler */
void DMA1_Channel3_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch3_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[2] != NULL){
		DMA_CallBacks[2]();
	}
}
/* DMA channel4 interrupt handler */
void DMA1_Channel4_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch4_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[3] != NULL){
		DMA_CallBacks[3]();
	}
}
/* DMA channel5 interrupt handler */
void DMA1_Channel5_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch5_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[4] != NULL){
		DMA_CallBacks[4]();
	}
}
/* DMA channel6 interrupt handler */
void DMA1_Channel6_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch6_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[5] != NULL){
		DMA_CallBacks[5]();
	}
}
/* DMA channel7 interrupt handler */
void DMA1_Channel7_IRQHandler(void){

	/* clearing interrupt flag */
	DMA->IFCR |= DMA_ch7_InterruptFlag_ClearMask;
	/* calling the call back function */
	if (DMA_CallBacks[6] != NULL){
		DMA_CallBacks[6]();
	}
}
