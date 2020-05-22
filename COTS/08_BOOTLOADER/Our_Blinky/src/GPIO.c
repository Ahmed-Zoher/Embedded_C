#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"

typedef struct
{
	volatile u32 CRL; 
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCK;
}GPIO_t;

extern STD_STATUS GPIO_u8ConfigurePin(void *Copy_pvGPIO, GPIO_Init_t* GPIO_InitStruct)
{
	u8 Local_u8PinIndex = 0;
	u32 Local_u32RegisterCopy = 0;
	u8 Local_u8PinConfig = 0;
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO(Copy_pvGPIO) && 
		IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin) && 
		IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed) && 
		IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode))
	{
		Local_u8PinConfig = (GPIO_InitStruct->GPIO_Speed | GPIO_InitStruct->GPIO_Mode);
		
		Local_u32RegisterCopy = GPIOx->CRL;
		for(Local_u8PinIndex = 0; Local_u8PinIndex < (REGISTER_SIZE/2); Local_u8PinIndex++)
		{
			if((GPIO_InitStruct->GPIO_Pin) & (1<<Local_u8PinIndex))
			{
				/* Configurations of CRL */
				
				/* Clear the old configurations for that pin */
				Local_u32RegisterCopy &= ~(((GPIO_SPEED_CLR_MASK | GPIO_MODE_CLR_MASK)) << (4 * Local_u8PinIndex));       //(GPIO_SPEED_CLR_MASK & GPIO_MODE_CLR_MASK) << (4 * Local_u8PinIndex);
				
				/* Assign the new pin configuration */
				Local_u32RegisterCopy |= (Local_u8PinConfig) << (4 * Local_u8PinIndex);
				
				/* The case of Input pull-up */
				if(GPIO_InitStruct->GPIO_Mode & GPIO_MODE_IN_PU_MASK)
				{
					GPIOx->BSRR = (1 << Local_u8PinIndex);
				}
			}
		}
		/* Write the new pin configurations to CRL */
		GPIOx->CRL = Local_u32RegisterCopy;
		
		Local_u32RegisterCopy = GPIOx->CRH;
		for(Local_u8PinIndex = (REGISTER_SIZE/2); Local_u8PinIndex < REGISTER_SIZE; Local_u8PinIndex++)
		{
			if((GPIO_InitStruct->GPIO_Pin) & (1<<Local_u8PinIndex))
			{
				/* Configurations of CRH */
				
				/* Clear the old configurations for that pin */
				Local_u32RegisterCopy &= ~(((GPIO_SPEED_CLR_MASK | GPIO_MODE_CLR_MASK)) << (4 * (Local_u8PinIndex - 8)));
				
				/* Assign the new pin configuration */
				Local_u32RegisterCopy |= (Local_u8PinConfig) << (4 * (Local_u8PinIndex - 8));
				
				/* The case of Input pull-up */
				if(GPIO_InitStruct->GPIO_Mode & GPIO_MODE_IN_PU_MASK)
				{
					GPIOx->BSRR = (1 << Local_u8PinIndex);
				}
			}
		}
		/* Write the new configurations to CRH */
		GPIOx->CRH = Local_u32RegisterCopy;
		
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS GPIO_u8WritePinValue(void *Copy_pvGPIO, uint16_t Copy_u16PinMask, LEVEL Copy_u8Level)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO_PIN(Copy_u16PinMask))
	{
		if(Copy_u8Level)
		{
			GPIOx -> BSRR = Copy_u16PinMask;
		}
		else
		{
			GPIOx -> BRR = Copy_u16PinMask;
		}
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

