/*****************************************/
/*Author	:	AHMED ZOHER& WALEED ADEL */
/*Version	: 	V01				         */
/*Date		:	17 Feb 2020		         */
/*****************************************/


#ifndef GPIO_GUARD_H
#define GPIO_GUARD_H


#define GPIO_PORTA   PORTA_t
#define GPIO_PORTB   PORTB_t
#define GPIO_PORTC   PORTC_t

#define GPIO_PIN0_MASK     ((u16)0x1)
#define GPIO_PIN1_MASK     ((u16)0x2)
#define GPIO_PIN2_MASK     ((u16)0x4)
#define GPIO_PIN3_MASK     ((u16)0x8)
#define GPIO_PIN4_MASK     ((u16)0x10)
#define GPIO_PIN5_MASK     ((u16)0x20)
#define GPIO_PIN6_MASK     ((u16)0x40)
#define GPIO_PIN7_MASK     ((u16)0x80)
#define GPIO_PIN8_MASK     ((u16)0x100)
#define GPIO_PIN9_MASK     ((u16)0x200)
#define GPIO_PIN10_MASK    ((u16)0x400)
#define GPIO_PIN11_MASK    ((u16)0x800)
#define GPIO_PIN12_MASK    ((u16)0x1000)
#define GPIO_PIN13_MASK    ((u16)0x2000)
#define GPIO_PIN14_MASK    ((u16)0x4000)
#define GPIO_PIN15_MASK    ((u16)0x8000)
#define GPIO_PIN_ALL_MASK  ((u16)0xFFFF)


#define GPIO_PIN0   ((u8)0x0)
#define GPIO_PIN1   ((u8)0x1)
#define GPIO_PIN2   ((u8)0x2)
#define GPIO_PIN3   ((u8)0x3)
#define GPIO_PIN4   ((u8)0x4)
#define GPIO_PIN5   ((u8)0x5)
#define GPIO_PIN6   ((u8)0x6)
#define GPIO_PIN7   ((u8)0x7)
#define GPIO_PIN8   ((u8)0x8)
#define GPIO_PIN9   ((u8)0x9)
#define GPIO_PIN10  ((u8)0xA)
#define GPIO_PIN11  ((u8)0xB)
#define GPIO_PIN12  ((u8)0xC)
#define GPIO_PIN13  ((u8)0xD)
#define GPIO_PIN14  ((u8)0xE)
#define GPIO_PIN15  ((u8)0xF)

#define PULL_UP          1
#define PULL_DOWN        0

#define INPUT_ANALOG				    ((u8)0)
#define INPUT_FLOATING				    ((u8)4)
#define INPUT_PULL_UP_DOWN			    ((u8)8)

#define OUTPUT_10MHz_PUSH_PULL			((u8)1)
#define OUTPUT_10MHz_DRAIN				((u8)5)
#define AlternateFn_10MHz_PUSH_PULL		((u8)9)
#define AlternateFn_10MHz_OPEN_DRAIN		((u8)13)

#define OUTPUT_2MHz_PUSH_PULL			((u8)2)
#define OUTPUT_2MHz_DRAIN				((u8)6)
#define AlternateFn_2MHz_PUSH_PULL		((u8)10)
#define AlternateFn_2MHz_OPEN_DRAIN		((u8)14)

#define OUTPUT_50MHz_PUSH_PULL			((u8)3)
#define OUTPUT_50MHz_DRAIN				((u8)7)
#define AlternateFn_50MHz_PUSH_PULL		((u8)11)
#define AlternateFn_50MHz_OPEN_DRAIN		((u8)15)

typedef struct{
    u32  CRL ;
    u32  CRH ;
    u32  IDR ;
    u32  ODR ;
    u32  BSRR;
    u32  BRR ;
    u32  LCKR;
}PORT_REG;

#define  PORTA_BASE_ADDRESS   0x40010800
#define PORTA_t  ((PORT_REG * const)PORTA_BASE_ADDRESS)

#define  PORTB_BASE_ADDRESS   0x40010C00
#define PORTB_t  ((PORT_REG * const)PORTB_BASE_ADDRESS)

#define  PORTC_BASE_ADDRESS   0x40011000
#define PORTC_t  ((PORT_REG * const)PORTC_BASE_ADDRESS)

typedef struct{
    u16 GPIO_u16Pin               ;
    u8  GPIO_u8PinMode            ;
    PORT_REG*  GPIO_ptrPort       ;
}GPIO_t;


/* Description: This API shall Set the Pin Configuration    */
/* Input  => GPIO_t {GPIO_u16Pin, GPIO_u8PinMode,           */
/*                              GPIO_ptrPort}               */
/* Output => void                                           */
extern void GPIO_voidSetPinMode(GPIO_t* Copy_structHandler);


/* Description: This API shall Set the Pin Value to ON, OFF */
/* Input  => PORT_REG {GPIO_PORTA, GPIO_PORTB,GPIO_PORTC}   */
/*        => Copy_u16Pin {GPIO_PIN0_MASK, GPIO_PIN1_MASK,   */
/*                       ,...........,GPIO_PIN_ALL_MASK}    */
/*        => Copy_u8Value {ON, OFF}                         */
/* Output => void                                           */
extern void GPIO_voidSetPinValue(PORT_REG* Copy_u32Port, u16 Copy_u16Pin, u8 Copy_u8Value);


/* Description: This API shall Set the Pin Value to ON, OFF */
/* Input  => PORT_REG {GPIO_PORTA, GPIO_PORTB,GPIO_PORTC}   */
/*        => Copy_u8Pin {GPIO_PIN0, GPIO_PIN1,..,GPIO_PIN15}*/
/* Output => PinValue {ON = 1, OFF = 0}                     */
extern u8 GPIO_u8GetPinValue(PORT_REG* Copy_u32Port, u8 Copy_u8Pin);

#endif
