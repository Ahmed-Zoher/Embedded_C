#include "STD_TYPES.h"
#include <dSTK.h>
#include <dSTK_Config.h>



/*****************************************/
/********** REGISTERS ADDRESSES **********/
/*****************************************/
#define SYSTCK_BASE_ADDRESS	0xE000E010
#define SYSTCK_CTRL			    *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x00))
#define SYSTCK_LOAD  	        *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x04))
#define SYSTCK_VAL  	        *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x08))
#define SYSTCK_CALIB  	        *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x0C))


/*****************************************/
/**************** MASKS ******************/
/*****************************************/
#define CLOCK_PRE_MASK           ((u32)0x00000004)
#define TICK_INT_MASK            ((u32)0x00000002)
#define ENABLE_MASK              ((u32)0x00000001)
#define RESET_COUNTFLAG          ((u32)0x00000000)


/*****************************************/
/************** VARIABLES ****************/
/*****************************************/
static STK_CBF_t APP_CBF;


/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
void STK_MCAL_Init(void){
    SYSTCK_CTRL |= TICK_INT_MASK;
    if (CLOCK_PRE == CLOCK_PRE_AHB_DIV8) 
         SYSTCK_CTRL &=~ CLOCK_PRE_MASK;
    else if (CLOCK_PRE == CLOCK_PRE_AHB)
         SYSTCK_CTRL |= CLOCK_PRE_MASK;
    else 
         SYSTCK_CTRL &=~ CLOCK_PRE_MASK;
}


void STK_MCAL_Start(void){
    SYSTCK_VAL = RESET_COUNTFLAG;
    SYSTCK_CTRL |= ENABLE_MASK;
}


void STK_MCAL_Stop(void){
    SYSTCK_CTRL &=~ ENABLE_MASK;
}


void STK_MCAL_SetTimeUS(u32 timeUS, u8 AHB_Clock_Hz){
    u32 Tick_time = 0;
    if (CLOCK_PRE == CLOCK_PRE_AHB_DIV8)
         Tick_time = (8/AHB_Clock_Hz);
    else 
         Tick_time = (1/AHB_Clock_Hz);
    u32 tempo = (timeUS/Tick_time);
    SYSTCK_LOAD = (timeUS/Tick_time);
}


void STK_MCAL_SetCallBack(STK_CBF_t CBF){
    if (CBF != NULL)
        APP_CBF = CBF;
}


void SysTick_Handler(void){
    if (APP_CBF != NULL)
        APP_CBF();
}
