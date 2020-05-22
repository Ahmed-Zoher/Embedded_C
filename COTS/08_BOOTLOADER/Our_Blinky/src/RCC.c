#include "RCC.h"

typedef struct
{
	volatile u32 CR;		/* Clock control register, offset = 0x00*/
	volatile u32 CFGR;		/* Clock configuration register, offset = 0x04 */
	volatile u32 CIR;		/* Clock interrupt register, offset = 0x08 */
	volatile u32 APB2RSTR;	/* APB2 peripheral reset register, offset = 0x0C */
	volatile u32 APB1RSTR;	/* APB1 peripheral reset register, offset = 0x10 */
	volatile u32 AHBENR;	/* AHB peripheral clock enable register, offset = 0x14 */
	volatile u32 APB2ENR;	/* APB2 peripheral clock enable register, offset = 0x18 */
	volatile u32 APB1ENR;	/* APB1 peripheral clock enable register, offset = 0x1C */
	volatile u32 BDCR;		/* Backup domain control register, offset = 0x20 */
	volatile u32 CSR;		/* Control/status register, offset = 0x24 */

}RCC_t;

/* This is a pointer to a block that corresponds to RCC memory map */
volatile RCC_t* const RCC = (RCC_t*)0x40021000;

/*note add the PLL multiplier*/

extern STD_STATUS RCC_u8ControlClks(u32 Copy_u32ClkSelectionMask, STATE Copy_u8Status)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_CLK_MASK_VALID(Copy_u32ClkSelectionMask))
	{
		switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->CR;
					Local_u32RegisterCopy &= ~Copy_u32ClkSelectionMask;
					RCC->CR = Local_u32RegisterCopy;
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				case ON:
				
					Local_u32RegisterCopy = RCC->CR;
					Local_u32RegisterCopy |= Copy_u32ClkSelectionMask;
					RCC->CR = Local_u32RegisterCopy;
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}		
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS RCC_u8SelectSysClk(u32 Copy_u32SysClkSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_SYS_CLK_MASK_VALID(Copy_u32SysClkSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_SW_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32SysClkSelectionMask;
		RCC->CFGR = Local_u32RegisterCopy;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
		
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS RCC_u8ControlPeripherals(BUS Copy_u8Bus, u32 Copy_u32PeripheralMask, STATE Copy_u8Status)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	switch(Copy_u8Bus)
	{
		case AHB:
			switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->AHBENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->AHBENR = Local_u32RegisterCopy;
					break;
					
				case ON:
			
					Local_u32RegisterCopy = RCC->AHBENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->AHBENR = Local_u32RegisterCopy;
					break;
			
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			break;

		case APB2:
			switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->APB2ENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->APB2ENR = Local_u32RegisterCopy;
					break;
				
				case ON:
				
					Local_u32RegisterCopy = RCC->APB2ENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->APB2ENR = Local_u32RegisterCopy;
					break;

				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			break;

		case APB1:
			switch(Copy_u8Status)
			{
				case OFF:
				
					Local_u32RegisterCopy = RCC->APB1ENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->APB1ENR = Local_u32RegisterCopy;
					break;
				
				case ON:
				
					Local_u32RegisterCopy = RCC->APB1ENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->APB1ENR = Local_u32RegisterCopy;
					break;

				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			break;

		default:
				
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
	}	
	return local_u8ErrorStatus;
}

