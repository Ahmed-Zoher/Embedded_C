
#define ACTIVE_HIGH 1
#define ACTIVE_LOW  0

#define ALARM_LED   0
#define BUZZER_LED  1
#define NUM_OF_LEDS 2


typedef struct{
    u8  GPIO_u8LED               ;
    u16 GPIO_u16Pin              ;
    u8  GPIO_u8PinMode           ;
    u8  GPIO_u8ActiveState       ;
    PORT_REG*  GPIO_ptrPort      ;
}LED_MAP_t;


extern void LED_H_voidSetLedState(u8 Copy_u8Led ,u8 Copy_u8LedState);
