/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#include "STD_TYPES.h"
#include <dRCC.h>
#include <dSTK.h>
#include <hSTK.h>


/*************************************************/
/********** Public Function Definitions **********/
/*************************************************/

/* Description: This Function shall do the following:
									1- Enable Systick Interrupt
									2- Configure AHB prescaler
 * Input      : void                                           
 * Output     : void                             */
void STK_Init(void){
   STK_MCAL_Init();
}


/* Description: This Function shall do the following:
									1- Reset Counting Flag
									2- Start Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
void STK_Start(void){
   STK_MCAL_Start();
}


/* Description: This Function shall stop the Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
void STK_Stop(void){
   STK_MCAL_Stop();
}


/* Description: This Function shall do the following:
									1- Calculate Tick Time (in US)
									2- Load Tick Time in the Systick Timer (time till overflow) 
 * Input      :  
                  1- u32 timeUS         
									Description: time user wants till interrupt occures
									Value      : any constant from 0 to (2^32 -1) 									
 * Output     : void                             */
void STK_SetTimeUS(u32 timeUS){
   u8 freq = RCC_GetSystemClockFreq();
   STK_MCAL_SetTimeUS(timeUS, freq);
}


/* Description: This Function sets Callback Function that's going to be called 
 * when systick interrupt is fired to notify user that a tick has passed 
 * Input      : 1- STK_CBF_t CBF
								Describtion: pointer to a function of type STK_CBF_t
								Value      : Address of the Callback function 
 * Output     : void                             */
void STK_SetCallBack(STK_CBF_t CBF){
   STK_MCAL_SetCallBack(CBF);
}

