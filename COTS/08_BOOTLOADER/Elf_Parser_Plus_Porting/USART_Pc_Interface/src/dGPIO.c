/*****************************************/
/*Author	:	AHMED ZOHER& WALEED ADEL */
/*Version	: 	V01				         */
/*Date		:	14 Jan 2020		         */
/*****************************************/
#include "STD_TYPES.h"
#include <dGPIO.h>






#define  GPIO_PIN_CLEAR_MASK  ((u8)0xF)


/* Description: This API shall Set the Pin Value to ON, OFF */
/* Input  => PORT_REG {GPIO_PORTA, GPIO_PORTB,GPIO_PORTC}   */
/*        => Copy_u16Pin {GPIO_PIN0_MASK, GPIO_PIN1_MASK,   */
/*                       ,...........,GPIO_PIN_ALL_MASK}    */
/*        => Copy_u8Value {ON, OFF}                         */
/* Output => void                                           */
void GPIO_voidSetPinValue(PORT_REG* Copy_u32Port, u16 Copy_u16Pin, u8 Copy_u8Value)
{
    if (Copy_u8Value == 1) 
        Copy_u32Port->BSRR=Copy_u16Pin;
    else
        Copy_u32Port->BRR=Copy_u16Pin;
}



u8 GPIO_u8GetPinValue(PORT_REG* Copy_u32Port, u8 Copy_u8Pin)
{
    return (Copy_u32Port->IDR >>Copy_u8Pin) &(0x01);
}


/* Description: This API shall Set the Pin Configuration    */
/* Input  => GPIO_t {GPIO_u16Pin, GPIO_u8PinMode,           */
/*                              GPIO_ptrPort}               */
/* Output => void                                           */
void GPIO_voidSetPinMode(GPIO_t* Copy_structHandler)
{
	u16 Local_u16Pin=Copy_structHandler->GPIO_u16Pin;
    for (u8 Local_u8LoopCounter = 0; Local_u8LoopCounter<16 ; Local_u8LoopCounter++){
      if (Local_u8LoopCounter <= 7 && (Local_u16Pin&0x01)){
          Copy_structHandler->GPIO_ptrPort->CRL &= ~(GPIO_PIN_CLEAR_MASK << (Local_u8LoopCounter*4));   //clear 4 bits
          Copy_structHandler->GPIO_ptrPort->CRL |=  (Copy_structHandler->GPIO_u8PinMode << (Local_u8LoopCounter*4));  //set Copy_u8Mode
      }else if(Local_u8LoopCounter <= 15 && (Local_u16Pin&0x01)){
          Copy_structHandler->GPIO_ptrPort->CRH &= ~(GPIO_PIN_CLEAR_MASK << ((Local_u8LoopCounter - 8)*4));
          Copy_structHandler->GPIO_ptrPort->CRH |=  (Copy_structHandler->GPIO_u8PinMode << ((Local_u8LoopCounter - 8)*4));
      }
      Local_u16Pin>>=1;
    }
}
