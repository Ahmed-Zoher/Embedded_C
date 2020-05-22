#ifndef GPIO_H
#define GPIO_H

#define REGISTER_SIZE 16

/*Type definitions*/

#define 	GPIOA		(void*)0x40010800
#define 	GPIOB		(void*)0x40010C00
#define 	GPIOC		(void*)0x40011000

typedef struct
{
	u16 GPIO_Pin;
	u8 GPIO_Speed;
	u8 GPIO_Mode;
	
}GPIO_Init_t;

#define 	IS_GPIO(GPIO) 	(((GPIO) == GPIOA) || \
                                ((GPIO) == GPIOB) || \
                                ((GPIO) == GPIOC))


/*GPIO Pins*/

#define 	GPIO_PIN_0			((u16)0x0001)
#define 	GPIO_PIN_1			((u16)0x0002)
#define 	GPIO_PIN_2			((u16)0x0004)
#define 	GPIO_PIN_3			((u16)0x0008)
#define 	GPIO_PIN_4			((u16)0x0010)
#define 	GPIO_PIN_5			((u16)0x0020)
#define 	GPIO_PIN_6			((u16)0x0040)
#define 	GPIO_PIN_7			((u16)0x0080)
#define 	GPIO_PIN_8			((u16)0x0100)
#define 	GPIO_PIN_9			((u16)0x0200)
#define 	GPIO_PIN_10			((u16)0x0400)
#define 	GPIO_PIN_11			((u16)0x0800)
#define 	GPIO_PIN_12			((u16)0x1000)
#define 	GPIO_PIN_13			((u16)0x2000)
#define 	GPIO_PIN_14			((u16)0x4000)
#define 	GPIO_PIN_15			((u16)0x8000)
#define 	GPIO_PIN_ALL		((u16)0xFFFF)

#define 	IS_GPIO_PIN(PIN) (((PIN) == GPIO_PIN_0) || \
                              ((PIN) == GPIO_PIN_1) || \
                              ((PIN) == GPIO_PIN_2) || \
                              ((PIN) == GPIO_PIN_3) || \
                              ((PIN) == GPIO_PIN_4) || \
                              ((PIN) == GPIO_PIN_5) || \
                              ((PIN) == GPIO_PIN_6) || \
                              ((PIN) == GPIO_PIN_7) || \
                              ((PIN) == GPIO_PIN_8) || \
                              ((PIN) == GPIO_PIN_9) || \
                              ((PIN) == GPIO_PIN_10) || \
                              ((PIN) == GPIO_PIN_11) || \
                              ((PIN) == GPIO_PIN_12) || \
                              ((PIN) == GPIO_PIN_13) || \
                              ((PIN) == GPIO_PIN_14) || \
                              ((PIN) == GPIO_PIN_15) || \
							  ((PIN) == GPIO_PIN_ALL))


/*CRL & CRLH Registers*/
#define 	GPIO_SPEED_INPUT_MASK				((u8)0x00)
#define 	GPIO_SPEED_10MHZ_MASK				((u8)0x01)
#define 	GPIO_SPEED_2MHZ_MASK				((u8)0x02)
#define 	GPIO_SPEED_50MHZ_MASK				((u8)0x03)
#define 	GPIO_SPEED_CLR_MASK					((uint32_t)0x00000003) //changed

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_INPUT_MASK) || ((SPEED) == GPIO_SPEED_10MHZ_MASK) || \
								((SPEED) == GPIO_SPEED_2MHZ_MASK) || ((SPEED) == GPIO_SPEED_50MHZ_MASK))

#define 	GPIO_MODE_IN_ANALOG_MASK			((u8)0x00)
#define 	GPIO_MODE_IN_FLOATING_MASK			((u8)0x04)
#define 	GPIO_MODE_IN_PU_MASK				((u8)0x08)
#define 	GPIO_MODE_IN_PD_MASK				((u8)0x08)
#define 	GPIO_MODE_OUT_PP_MASK				((u8)0x00)
#define 	GPIO_MODE_OUT_OD_MASK				((u8)0x04)
#define 	GPIO_MODE_AF_PP_MASK				((u8)0x08)
#define 	GPIO_MODE_AF_OD_MASK				((u8)0x0C)
#define 	GPIO_MODE_CLR_MASK					((uint32_t)0x0000000C) //changed


#define IS_GPIO_MODE(MODE)	(((MODE) == GPIO_MODE_IN_ANALOG_MASK) || ((MODE) == GPIO_MODE_IN_FLOATING_MASK) || \
                            ((MODE) == GPIO_MODE_IN_PU_MASK) || ((MODE) == GPIO_MODE_IN_PD_MASK) || \
                            ((MODE) == GPIO_MODE_OUT_PP_MASK) || ((MODE) == GPIO_MODE_OUT_OD_MASK) || \
                            ((MODE) == GPIO_MODE_AF_PP_MASK) || ((MODE) == GPIO_MODE_AF_OD_MASK))

extern STD_STATUS GPIO_u8ConfigurePin(void *Copy_pvGPIO, GPIO_Init_t* GPIO_InitStruct);

extern STD_STATUS GPIO_u8WritePinValue(void *Copy_pvGPIO, u16 Copy_u16PinMask, LEVEL Copy_u8Level);

#endif /*GPIO_H*/
