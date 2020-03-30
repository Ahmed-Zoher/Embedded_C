#ifndef HLCD_CONFIG_H
#define HLCD_CONFIG_H


/*
    NUMBER_OF_LINES: ONE_LINE
                     TWO_LINE
*/
#define NUMBER_OF_LINES     TWO_LINE

/*
    FONT: FONT_5x7
          FONT_5x10/
*/
#define FONT                FONT_5x7

/*
    DISPLAY: DISPLAY_ON
             DISPLAY_OFF
*/
#define DISPLAY             DISPLAY_ON

/*
    CURSOR: CURSOR_ON
            CURSOR_OFF
*/
#define CURSOR               CURSOR_ON

/*
    BLINK: BLINK_ON
           BLINK_OFF
*/
#define BLINK                BLINK_OFF

/*
    INC_DEC: INCREASE
             DECREASE
*/
#define INC_DEC              INCREASE

/*
    SHIFT: SHIFT_ON
           SHIFT_OFF
*/
#define SHIFT                SHIFT_OFF


#define LCD_CTRL_PORT       PORTC_t
#define LCD_DATA_PORT       PORTA_t

#define LCD_CTRL_PINS_MODE  OUTPUT_10MHz_PUSH_PULL
#define LCD_DATA_PINS_MODE  OUTPUT_10MHz_PUSH_PULL

#define RS                  GPIO_PIN13_MASK
#define RW                  GPIO_PIN14_MASK
#define E                   GPIO_PIN15_MASK
#define D0                  GPIO_PIN0_MASK
#define D1                  GPIO_PIN1_MASK
#define D2                  GPIO_PIN2_MASK
#define D3                  GPIO_PIN3_MASK
#define D4                  GPIO_PIN4_MASK
#define D5                  GPIO_PIN5_MASK
#define D6                  GPIO_PIN6_MASK
#define D7                  GPIO_PIN7_MASK

#endif
