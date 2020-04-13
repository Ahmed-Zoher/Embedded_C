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
#ifndef dDMA_H
#define dDMA_H

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

/* DMA Channel Number */
#define DMA_Channel_1                                   ((u8)0x0)
#define DMA_Channel_2                                   ((u8)0x1)
#define DMA_Channel_3                                   ((u8)0x2)
#define DMA_Channel_4                                   ((u8)0x3)
#define DMA_Channel_5                                   ((u8)0x4)
#define DMA_Channel_6                                   ((u8)0x5)
#define DMA_Channel_7                                   ((u8)0x6)


/* DMA_InitTypeDef_t configurations */

#define DMA_DirectionMemToPer                    ((u32)0x00000010)
#define DMA_DirectionPerToMem                    ((u32)0x00000000)

#define DMA_PeripheralIncrement_Enable           ((u32)0x00000040)
#define DMA_PeripheralIncrement_Disable          ((u32)0x00000000)

#define DMA_MemoryIncrement_Enable               ((u32)0x00000080)
#define DMA_MemoryIncrement_Disable              ((u32)0x00000000)

#define DMA_PeripheralDataWidth_8_bit            ((u32)0x00000000)
#define DMA_PeripheralDataWidth_16_bit           ((u32)0x00000100)
#define DMA_PeripheralDataWidth_32_bit           ((u32)0x00000200)

#define DMA_MemoryDataWidth_8_bit                ((u32)0x00000000)
#define DMA_MemoryDataWidth_16_bit               ((u32)0x00000400)
#define DMA_MemoryDataWidth_32_bit               ((u32)0x00000800)

#define DMA_CircularMode_Enable                  ((u32)0x00000020)
#define DMA_CircularMode_Disable                 ((u32)0x00000000)

#define DMA_ChannelPriority_VeryHigh             ((u32)0x00003000)
#define DMA_ChannelPriority_High                 ((u32)0x00002000)
#define DMA_ChannelPriority_Medium               ((u32)0x00001000)
#define DMA_ChannelPriority_Low                  ((u32)0x00000000)

#define DMA_Mem2Mem_Enable                       ((u32)0x00004000)
#define DMA_Mem2Mem_Disable                      ((u32)0x00000000)

#define DMA_HalfTransfer_Enable                  ((u32)0x00000004)
#define DMA_HalfTransfer_Disable                 ((u32)0x00000000)

#define DMA_ErrorInterrupt_Enable                ((u32)0x00000008)
#define DMA_ErrorInterrupt_Disable               ((u32)0x00000000)

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef struct
{
  /*Specifies the peripheral base address for DMA Channelx. */
  u32 DMA_PeripheralBaseAddress;  
  /* Specifies the memory base address for DMA Channelx. */
  u32 DMA_MemoryBaseAddress;
  /* Specifies if the peripheral is the source or destination*/
  u32 DMA_Direction; 
  /* Counter value */
  u32 DMA_DataCount;
  /* Specifies whether the Peripheral address register is incremented or not */
  u32 DMA_PeripheralIncrement;
  /* Specifies whether the memory address register is incremented or not */
  u32 DMA_MemoryIncrement;
  /* Specifies the peripheral data width */
  u32 DMA_PeripheralDataWidth;
  /* Specifies the memory data width */ 
  u32 DMA_MemoryDataWidth;
  /* Enables or Disables the circular mode */
  u32 DMA_CircularMode;
  /* DMA channel software priority */
  u32 DMA_ChannelPriority;
  /* Specifies if the DMA Channelx will be used in memory-to-memory transfer. */
  u32 DMA_Mem2Mem;
  /* Enables or Disables the Half-Transfer mode */
  u32 DMA_HalfTransfer;
  /* Enables or Disables the Error Interrupt */
  u32 DMA_ErrorInterrupt;
  

}DMA_InitTypeDef_t;


/************************************************************/
/****************** VARIABLES DECLARATIONS ******************/
/************************************************************/
typedef void(*DMA_CallBackFn)(void);



/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/


extern void dDMA_Init( u8 DMA_Channel, DMA_InitTypeDef_t * DMA_InitStruct);
extern void dDMA_GetCurrentDataCounter(u8 DMA_Channel, u16 * CurrentDataCounter);
extern void dDMA_Start(u8 DMA_Channel);
extern void dDMA_Configure(u8 DMA_Channel, DMA_InitTypeDef_t * DMA_InitStruct);
extern void dDMA_SetCallBackFn(u8 DMA_Channel , DMA_CallBackFn DMA_CallBack);


#endif

