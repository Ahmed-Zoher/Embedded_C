/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#include "STD_TYPES.h"
#include <dSTK.h>
#include <dSTK_Config.h>


/*************************************************/
/****** Definitions & Static Configurations ******/
/*************************************************/

/************* Registers Addresses ***************/

#define SYSTCK_BASE_ADDRESS	    0xE000E010
#define SYSTCK_CTRL			        *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x00))
#define SYSTCK_LOAD  	          *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x04))
#define SYSTCK_VAL  	          *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x08))
#define SYSTCK_CALIB  	        *((volatile u32 *)(SYSTCK_BASE_ADDRESS + 0x0C))

/******************** MASKS **********************/

#define CLOCK_PRE_MASK           ((u32)0x00000004)
#define TICK_INT_MASK            ((u32)0x00000002)
#define ENABLE_MASK              ((u32)0x00000001)
#define RESET_COUNTFLAG          ((u32)0x00000000)


/*************************************************/
/******** UserDefined Types Declarations *********/
/*************************************************/
static STK_CBF_t APP_CBF;


/*************************************************/
/********** Public Function Definitions **********/
/*************************************************/

/* Description: This Function shall do the following:
									1- Enable Systick Interrupt
									2- Configure AHB prescaler
 * Input      : void                                           
 * Output     : void                             */
void STK_MCAL_Init(void){
    SYSTCK_CTRL |= TICK_INT_MASK;
    if (CLOCK_PRE == CLOCK_PRE_AHB_DIV8) 
         SYSTCK_CTRL &=~ CLOCK_PRE_MASK;
    else if (CLOCK_PRE == CLOCK_PRE_AHB)
         SYSTCK_CTRL |= CLOCK_PRE_MASK;
    else 
         SYSTCK_CTRL &=~ CLOCK_PRE_MASK;
}


/* Description: This Function shall do the following:
									1- Reset Counting Flag
									2- Start Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
void STK_MCAL_Start(void){
    SYSTCK_VAL = RESET_COUNTFLAG;
    SYSTCK_CTRL |= ENABLE_MASK;
}


/* Description: This Function shall stop the Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
void STK_MCAL_Stop(void){
    SYSTCK_CTRL &=~ ENABLE_MASK;
}


/* Description: This Function shall do the following:
									1- Calculate Tick Time (in US)
									2- Load Tick Time in the Systick Timer (time till overflow) 
 * Input      :  
                  1- u32 timeUS         
									Description: time user wants till interrupt occures
									Value      : any constant from 0 to (2^32 -1) 
                  2- u8  AHB_Clock_MHz  
									Description: frequency of AHB bus in MHz
                  Value      : 8, 36,..,72 Mhz 									
 * Output     : void                             */
void STK_MCAL_SetTimeUS(u32 timeUS, u8 AHB_Clock_MHz){
    u32 Tick_time = 0;
    if (CLOCK_PRE == CLOCK_PRE_AHB_DIV8)
         Tick_time = (8/AHB_Clock_MHz);
    else 
         Tick_time = (1/AHB_Clock_MHz);
    u32 tempo = (timeUS/Tick_time);
    SYSTCK_LOAD = (timeUS/Tick_time);
}


/* Description: This Function sets Callback Function that's going to be called 
 * when systick interrupt is fired to notify user that a tick has passed 
 * Input      : 1- STK_CBF_t CBF
								Description: pointer to a function of type STK_CBF_t
								Value      : Address of the Callback function 
 * Output     : void                             */
void STK_MCAL_SetCallBack(STK_CBF_t CBF){
    if (CBF != NULL)
        APP_CBF = CBF;
}


/* SysTick_Handler Implementation */
void SysTick_Handler(void){
    if (APP_CBF != NULL)
        APP_CBF();
}
