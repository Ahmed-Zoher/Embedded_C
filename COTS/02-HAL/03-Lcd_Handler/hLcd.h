#ifndef HLCD_H
#define HLCD_H


/*********************************************************/
/*************************Defines*************************/
/*********************************************************/
#define N_Rows_1             1
#define N_Rows_2             2
#define ONE_LINE             0
#define TWO_LINE             1
#define FONT_5x7             0
#define FONT_5x10            1
#define DISPLAY_ON           1
#define DISPLAY_OFF          0
#define CURSOR_ON            1
#define CURSOR_OFF           0
#define BLINK_ON             1
#define BLINK_OFF            0
#define INCREASE             1
#define DECREASE             0
#define SHIFT_ON             1
#define SHIFT_OFF            0
#define IS_COMMAND           0
#define IS_DATA              1


/*********************************************************/
/******************Variables Declarations*****************/
/*********************************************************/
typedef enum{
    STATUS_OK,
    STATUS_BUSY,
    STATUS_ERROR
}Status_t;


/*********************************************************/
/******************Function Declarations******************/
/*********************************************************/
void hLcd_Init(void);
Status_t hLcd_WriteCopy(u8 * String, u8 Length);
Status_t hLcd_WriteZeroCopy(u8 * String, u8 Length);
Status_t hLcd_MoveCursor(u8 Row, u8 Column);
Status_t hLcd_Clear(void);
Status_t hLcd_setWriteNotification(void(*NotificationFn)(void));
Status_t hLcd_setClearNotification(void(*NotificationFn)(void));
Status_t hLcd_setMoveNotification(void(*NotificationFn)(void));

#endif
