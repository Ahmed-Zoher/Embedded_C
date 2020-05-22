/************************************************************/
/****************** HEADER-FILES INCLUSION ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "dRCC.h"
#include "dFlash.h"
#include "hUSART.h"
#include "hSwitch.h"
#include "Delay.h"

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define MARKER_NO_APP				((u32)0xFFFFFFFF)
#define MARKER_APP_1				((u32)0xBBBBBBBB)
#define MARKER_APP_2				((u32)0xCCCCCCCC)
#define MARKER_FLASH_NEW_BOOTL		((u32)0xDDDDDDDD)

#define APP1						((u8)0X01)
#define APP2						((u8)0X02)

#define MARKER_ADDRESS				((u32)0x08003000)
#define MARKER						*((u32 *)MARKER_ADDRESS)

#define ENTRY_POINT_1_ADDRESS		((u32)0x08003004)
#define ENTRY_POINT_1				*((u32 *)ENTRY_POINT_1_ADDRESS)

#define ENTRY_POINT_2_ADDRESS		(ENTRY_POINT_1_ADDRESS)
#define ENTRY_POINT_2				*((u32 *)ENTRY_POINT_2_ADDRESS)

#define SCB_AIRCR					*((volatile u32 *)0xE000ED0C)
#define SYS_RESET_REQ_MASK			((u32)0x00000004)
#define SCB_AIRCR_KEY				((u32)0x05FA0000)

#define SECTOR_SIZE					((u16)1024)
#define NEW_APP_FRAME_SIZE			((u8)16)
#define ACK_SIZE					((u8)1)

#define BOOTLOADER_USARTx			((u8)USART1)

#define KEY_VALUE					((u8)0x11)

#define ACK							((u8)0x1)
#define NACK						((u8)0x2)
#define END_OF_FRAME_ACK			((u8)0x3)

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/



typedef struct {
	u32 ValidationKey;
	u32 AppNumber;
	u32 StartAddress;
	u32 NumberOfSectors;
	u32 EntryPoint;
}FlashNewAppCmd_t;

typedef void(*AppFunction)(void);

/************************************************************/
/****************** VARIABLES DEFINITIONS ******************/
/************************************************************/
FlashNewAppCmd_t FlashNewAppFrame;

USART_InitTypeDef USART_InitStruct;

FlashNewAppCmd_t FlashNewAppCmd;
u8 RxSectorBuffer [SECTOR_SIZE];

u8 FirstTimeFlag		= 1;
u8 ReceivingData		= 0;
u8 FrameReceived		= 0;
u8 SectorAckTransmitted	= 0;
u8 Status				= NACK;
u16 SectorCounter		= 0;

/************************************************************/
/****************** FUNCTION DEFINITIONS ********************/
/************************************************************/
// Forward declarations
void SetJumpPoint(unsigned int JumpPoint)
{
	/* Re-initializing the Stack Pointer */
	__asm__("MOV PC, R0");
}



void USART_RX_handler(void)
{
	if (FirstTimeFlag)
	{
		if ( KEY_VALUE == FlashNewAppCmd.ValidationKey )
		{
			GPIO_voidSetPinValue(GPIO_PORTC, GPIO_PIN14_MASK, 1);
			Status = ACK;
		}
		else
		{
			Status = NACK;
		}
	}
	else if (ReceivingData)
	{
		dFLASH_unlock();
		dFLASH_erasePage((void *)FlashNewAppCmd.StartAddress +(SectorCounter*SECTOR_SIZE));

		dFLASH_unlock();
		dFLASH_programWrite( (void *) (FlashNewAppCmd.StartAddress +(SectorCounter*SECTOR_SIZE)),
				(void *)RxSectorBuffer, SECTOR_SIZE);
		SectorCounter++;
		Status = ACK;
	}
	FrameReceived = 1;
}

void USART_TX_handler(void)
{
	/* ACK of Header transmission */
	if (FirstTimeFlag)
	{
		if( ACK == Status )
		{

			ReceivingData = 1;
			FirstTimeFlag = 0;
		}
		else
		{
			ReceivingData = 0;
			FirstTimeFlag = 1;
		}
	}
	if (ReceivingData)
	{
		SectorAckTransmitted = 1;
	}
	else
	{
		if ( APP1 == FlashNewAppCmd.AppNumber)
		{
			u32 EntryPoint2 = ENTRY_POINT_2;

			dFLASH_unlock();
			dFLASH_erasePage(MARKER_ADDRESS);

			dFLASH_writeWord((void *)MARKER_ADDRESS, MARKER_APP_1);
			dFLASH_writeWord((void *)ENTRY_POINT_1_ADDRESS, FlashNewAppCmd.EntryPoint);
			dFLASH_writeWord((void *)ENTRY_POINT_2_ADDRESS, EntryPoint2);
		}
		else if (APP2 == FlashNewAppCmd.AppNumber)
		{

			u32 EntryPoint1 = ENTRY_POINT_1;

			dFLASH_unlock();
			dFLASH_erasePage(MARKER_ADDRESS);

			dFLASH_writeWord((void *)MARKER_ADDRESS, MARKER_APP_2);
			dFLASH_writeWord((void *)ENTRY_POINT_1_ADDRESS, EntryPoint1);
			dFLASH_writeWord((void *)ENTRY_POINT_2_ADDRESS, FlashNewAppCmd.EntryPoint);
		}
		FirstTimeFlag = 1;
	}
}

void main(void)
{
//	dFLASH_unlock();
//	dFLASH_erasePage(MARKER_ADDRESS);
//	dFLASH_writeWord((void *)MARKER_ADDRESS, MARKER_NO_APP);

	RCC_SetPrephiralClockState( APB2, IOPAEN, ON);
	RCC_SetPrephiralClockState( APB2, IOPBEN, ON);
	RCC_SetPrephiralClockState( APB2, IOPCEN, ON);

	GPIO_t LED_RED = {GPIO_PIN14_MASK, OUTPUT_10MHz_PUSH_PULL, GPIO_PORTC};
	GPIO_t GREEN_RED = {GPIO_PIN7_MASK, OUTPUT_10MHz_PUSH_PULL, GPIO_PORTA};

	GPIO_voidSetPinMode(&LED_RED);
	GPIO_voidSetPinMode(&GREEN_RED);

	GPIO_voidSetPinValue(GPIO_PORTC, GPIO_PIN14_MASK, 0);
	GPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN7_MASK, 0);


	hSwitch_Init();
	if ( hSwitch_GetSwitchState(Switch_Flash) )
	{
		u32 EntryPoint1 = ENTRY_POINT_1;
		u32 EntryPoint2 = ENTRY_POINT_2;

		dFLASH_unlock();
		dFLASH_erasePage(MARKER_ADDRESS);

		dFLASH_writeWord((void *)ENTRY_POINT_1_ADDRESS, EntryPoint1);
		dFLASH_writeWord((void *)ENTRY_POINT_2_ADDRESS, EntryPoint2);
		dFLASH_writeWord((void *)MARKER_ADDRESS, MARKER_NO_APP);
	}
	switch (MARKER)
	{
		case MARKER_APP_1:
			SetJumpPoint(ENTRY_POINT_1);
			break;

		case MARKER_APP_2:
			SetJumpPoint(ENTRY_POINT_2);
			break;

		case MARKER_FLASH_NEW_BOOTL :
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			break;
		case MARKER_NO_APP:
			hUSART_StructDefaultInit(&USART_InitStruct);
			hUSART_Init(BOOTLOADER_USARTx,&USART_InitStruct);
			hUSART_SetTxCallBackFn(BOOTLOADER_USARTx,USART_TX_handler);
			hUSART_SetRxCallBackFn(BOOTLOADER_USARTx,USART_RX_handler);
			hUSART_Receive(BOOTLOADER_USARTx, (u8 *)&FlashNewAppCmd, sizeof(FlashNewAppCmd_t));
			while(1)
			{
				if(FrameReceived)
				{
					if( FlashNewAppCmd.NumberOfSectors == SectorCounter ){
						SectorCounter = 0;
						ReceivingData = 0;
						Status = END_OF_FRAME_ACK;
					}
					FrameReceived = 0;
					_delay_ms(1000);
					hUSART_Send(BOOTLOADER_USARTx, &Status, ACK_SIZE);
				}
				if (SectorAckTransmitted)
				{
					SectorAckTransmitted = 0;
					hUSART_Receive(BOOTLOADER_USARTx, RxSectorBuffer, SECTOR_SIZE);
				}
				if (MARKER != MARKER_NO_APP){
					/* unlocking the SCB_AIRCR register and triggering SW reset */
					SCB_AIRCR = (SCB_AIRCR_KEY | SYS_RESET_REQ_MASK);
				}
			}
			break;
	}
}
