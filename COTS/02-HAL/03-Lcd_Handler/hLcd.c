#include "STD_TYPES.h"
#include <dGPIO.h>
#include <hLcd.h>
#include <hLcd_Config.h>



/*********************************************************/
/*************************Defines*************************/
/*********************************************************/
#define LCD_LINE_1_CMD       0x80
#define LCD_LINE_2_CMD       0xC0

#define CLEAR_COMMAND        0b00000001

#define Conc(b7, b6, b5, b4, b3, b2, b1, b0)        Conc_Help(b7, b6, b5, b4, b3, b2, b1, b0)
#define Conc_Help(b7, b6, b5, b4, b3, b2, b1, b0)   0b##b7##b6##b5##b4##b3##b2##b1##b0

#define initState_S0_DATA                           (Conc(0,0,1,1,NUMBER_OF_LINES,FONT,0,0))
#define initState_S1_DATA                           (Conc(0,0,0,0,1,DISPLAY,CURSOR,BLINK))
#define initState_S2_DATA                           (Conc(0,0,0,0,0,0,0,1))
#define initState_S3_DATA                           (Conc(0,0,0,0,0,1,INC_DEC,SHIFT))


/*********************************************************/
/******************Variable Declarations******************/
/*********************************************************/
typedef enum {
    idle,
    WriteReq,
    ClearReq,
    CursorMoveReq
}State;

typedef enum {
    initState_S0,
    initState_S1,
    initState_S2,
    initState_S3
}initState_t;


/*********************************************************/
/*******************Variable Definitions******************/
/*********************************************************/
GPIO_t LcdCtrlPins = {.GPIO_u16Pin = (RS | RW | E),
                      .GPIO_u8PinMode = LCD_CTRL_PINS_MODE,
                      .GPIO_ptrPort = LCD_CTRL_PORT};

GPIO_t LcdDataPins = {.GPIO_u16Pin = (D0 | D1 | D2 | D3 | D4 | D5 | D6 |D7),
                      .GPIO_u8PinMode = LCD_DATA_PINS_MODE,
                      .GPIO_ptrPort = LCD_DATA_PORT};


State CurrentState = idle;
u8* tempChar;
u8* UserString;
u8  UserStringLength;
u8  UserRow;
u8  UserColumn;
u8  isInitDone;
u8  isEnabled;

void (*WriteDone)(void);
void (*ClearDone)(void);
void (*MoveDone)(void);


/*********************************************************/
/*******************PrivateFn Prototypes******************/
/*********************************************************/

static void WriteProcess(void);
static void ClearProcess(void);
static void MoveProcess(void);
static void InitProcess(void);
static void Write(u8 Data , u8 IS_CMD_OR_DATA);


/*********************************************************/
/*******************Function Definitions******************/
/*********************************************************/
void hLcd_Init(void){
    /*For 8 Bit Mode*/
    GPIO_voidSetPinMode(&LcdCtrlPins);
    GPIO_voidSetPinMode(&LcdDataPins);
}


Status_t hLcd_WriteCopy(u8 * String, u8 Length){
    Status_t local_State = STATUS_OK;
    if (CurrentState == idle){
        CurrentState = WriteReq;
        UserStringLength = Length;
        for (u8 Loop_Counter = 0; Loop_Counter < Length ; Loop_Counter++){
        	UserString[Loop_Counter] = String[Loop_Counter];
        }
    }
    else
        local_State = STATUS_BUSY;
    return local_State;
}


Status_t hLcd_WriteZeroCopy(u8 * String, u8 Length){
    Status_t local_State = STATUS_OK;
    if (CurrentState == idle){
        CurrentState = WriteReq;
        UserStringLength = Length;
        UserString = String;
    }
    else
        local_State = STATUS_BUSY;

    return local_State;
}


Status_t hLcd_MoveCursor(u8 N_Rows, u8 N_Columns){
    Status_t local_State = STATUS_OK;
    if (CurrentState == idle){
        CurrentState = CursorMoveReq;
        UserRow = N_Rows;
        UserColumn = N_Columns;
    }
    else
        local_State = STATUS_BUSY;
    return local_State;
}


Status_t hLcd_Clear(void){
    Status_t local_State = STATUS_OK;
    if (CurrentState == idle){
        CurrentState = ClearReq;
    }
    else
        local_State = STATUS_BUSY;
    return local_State;
}


Status_t hLcd_setWriteNotification(void(*NotificationFn)(void)){
    Status_t local_State = STATUS_OK;
    if(NotificationFn != NULL){
        WriteDone = NotificationFn;
    }
    else 
        local_State = STATUS_ERROR;
    return local_State;
}


Status_t hLcd_setClearNotification(void(*NotificationFn)(void)){
    Status_t local_State = STATUS_OK;
    if(NotificationFn != NULL){
        ClearDone = NotificationFn;
    }
    else 
        local_State = STATUS_ERROR;
    return local_State;
}


Status_t hLcd_setMoveNotification(void(*NotificationFn)(void)){
    Status_t local_State = STATUS_OK;
    if(NotificationFn != NULL){
        MoveDone = NotificationFn;
    }
    else 
        local_State = STATUS_ERROR;
    return local_State;
}


void hLcd_Task(void){
    if (isInitDone){
        switch (CurrentState) {
            case idle:                                 break;
            case WriteReq:       WriteProcess();       break;
            case ClearReq:       ClearProcess();       break;
            case CursorMoveReq:  MoveProcess();        break;
        }
    }else{
        InitProcess();
    }
}


void Write(u8 Data , u8 IS_CMD_OR_DATA){
    if (IS_CMD_OR_DATA == IS_COMMAND){
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,RS,OFF);
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,RW,OFF);
    }else if (IS_CMD_OR_DATA == IS_DATA){
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,RS,ON);
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,RW,OFF);
    }else {
        return ;
    }
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D0,(Data&(1<<0)));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D1,((Data&(1<<1))>>1));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D2,((Data&(1<<2))>>2));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D3,((Data&(1<<3))>>3));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D4,((Data&(1<<4))>>4));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D5,((Data&(1<<5))>>5));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D6,((Data&(1<<6))>>6));
    GPIO_voidSetPinValue(LcdDataPins.GPIO_ptrPort,D7,((Data&(1<<7))>>7));
}


void InitProcess(void){

    static initState_t currentInitState = initState_S0;
    switch (currentInitState) {
        case initState_S0:
            if(isEnabled == 1){
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
                isEnabled = 0;
                currentInitState = initState_S1;
            }else{
                Write(initState_S0_DATA,IS_COMMAND);
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
                isEnabled = 1;
            }
        break;
        case initState_S1:
            if(isEnabled == 1){
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
                isEnabled = 0;
                currentInitState = initState_S2;
            }else{
                Write(initState_S1_DATA,IS_COMMAND);
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
                isEnabled = 1;
            }
        break;
        case initState_S2:
            if(isEnabled == 1){
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
                isEnabled = 0;
                currentInitState = initState_S3;
            }else{
                Write(initState_S2_DATA,IS_COMMAND);
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
                isEnabled = 1;
            }
        break;
        case initState_S3:
            if(isEnabled == 1){
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
                isEnabled  = 0;
                isInitDone = 1;
            }else{
                Write(initState_S3_DATA,IS_COMMAND);
                GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
                isEnabled = 1;
            }
        break;
    }
}


void WriteProcess(void){
    static u8 CurrentCharacter = 0;
    if(isEnabled == 1){
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
        isEnabled = 0;
    }
    else{
        if (CurrentCharacter == UserStringLength){
            CurrentCharacter = 0;
            CurrentState = idle;
            WriteDone();
        }else{
        	//trace_printf("%x\t%c\n",UserString[CurrentCharacter],UserString[CurrentCharacter]);
            Write(UserString[CurrentCharacter],IS_DATA);
            //Write(tempChar[CurrentCharacter],IS_DATA);

            CurrentCharacter++;
            GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
            isEnabled = 1;
            
        }
    }
}


void ClearProcess(void){
    if(isEnabled == 1){
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
        isEnabled = 0;
        CurrentState = idle;
        ClearDone();
    }
    else{
        Write(CLEAR_COMMAND,IS_COMMAND);
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
        isEnabled = 1;
    }
}


void MoveProcess(void){
    if(isEnabled == 1){
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,OFF);
        isEnabled = 0;
        CurrentState = idle;
        MoveDone();
    }
    else{
        if (UserRow == N_Rows_1)
            Write(LCD_LINE_1_CMD + UserColumn, IS_COMMAND);
        else if (UserRow == N_Rows_2)
            Write(LCD_LINE_2_CMD + UserColumn, IS_COMMAND);
        GPIO_voidSetPinValue(LcdCtrlPins.GPIO_ptrPort,E,ON);
        isEnabled = 1;
    }
}
