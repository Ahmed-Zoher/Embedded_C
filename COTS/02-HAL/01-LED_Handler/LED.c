#include "STD_TYPES.h"
#include "GPIO.h"
#include "LED.h"


/* Description: This API shall Set the LED to be ON or OFF  */
/* Input  => Copy_u8Led {LED_NAME}                          */
/*        => State { ON, OFF}                               */
/* Output => void                                           */
void LED_H_voidSetLedState(u8 Copy_u8Led ,u8 Copy_u8LedState){
    extern LED_MAP_t map[];
    extern GPIO_t LEDS[];
    GPIO_voidSetPinMode(&LEDS[Copy_u8Led]);
    if (map[Copy_u8Led].GPIO_u8ActiveState == ACTIVE_HIGH){
        if (Copy_u8LedState == ON){
            GPIO_voidSetPinValue(map[Copy_u8Led].GPIO_ptrPort,map[Copy_u8Led].GPIO_u16Pin,ON);
        }else if (Copy_u8LedState == OFF){
            GPIO_voidSetPinValue(map[Copy_u8Led].GPIO_ptrPort,map[Copy_u8Led].GPIO_u16Pin,OFF);
        }
    }else{
        if (Copy_u8LedState == ON){
            GPIO_voidSetPinValue(map[Copy_u8Led].GPIO_ptrPort,map[Copy_u8Led].GPIO_u16Pin,OFF);
        }else if (Copy_u8LedState == OFF){
            GPIO_voidSetPinValue(map[Copy_u8Led].GPIO_ptrPort,map[Copy_u8Led].GPIO_u16Pin,ON);
        }
    }
}
