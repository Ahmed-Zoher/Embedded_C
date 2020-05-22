#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "Delay.h"


void main(void)
{
	trace_printf("We've reached the start of the main function\n");


	GPIO_Init_t LED_GREEN =
	{

			.GPIO_Pin = GPIO_PIN_13,
			.GPIO_Speed = GPIO_SPEED_2MHZ_MASK,
			.GPIO_Mode = GPIO_MODE_OUT_PP_MASK
	};


	RCC_u8ControlClks(RCC_CR_HSION_MASK, ON);
	RCC_u8SelectSysClk(RCC_CFGR_SW_HSI_MASK);
	RCC_u8ControlPeripherals(APB2, RCC_APB2ENR_IOPCEN_MASK, ON);

	GPIO_u8ConfigurePin(GPIOC, &LED_GREEN);

	trace_printf("We've reached before the main while\n");

	while (1)
	{
		GPIO_u8WritePinValue(GPIOC, LED_GREEN.GPIO_Pin, HIGH);
		_delay_ms(500);

		GPIO_u8WritePinValue(GPIOC, LED_GREEN.GPIO_Pin, LOW);
		_delay_ms(500);
	}
}

