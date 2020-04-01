/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#ifndef hSTK_H
#define hSTK_H

/*************************************************/
/********** Public Function Prototypes ***********/
/*************************************************/

/* Description: This Function shall do the following:
									1- Enable Systick Interrupt
									2- Configure AHB prescaler
 * Input      : void                                           
 * Output     : void                             */
extern void STK_Init(void);

/* Description: This Function shall do the following:
									1- Reset Counting Flag
									2- Start Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
extern void STK_Start(void);

/* Description: This Function shall stop the Systick Timer 
 * Input      : void                                           
 * Output     : void                             */
extern void STK_Stop(void);

/* Description: This Function shall do the following:
									1- Calculate Tick Time (in US)
									2- Load Tick Time in the Systick Timer (time till overflow) 
 * Input      :  
                  1- u32 timeUS         
									Description: time user wants till interrupt occures
									Value      : any constant from 0 to (2^32 -1) 									
 * Output     : void                             */
extern void STK_SetTimeUS(u32 timeUS);

/* Description: This Function sets Callback Function that's going to be called 
 * when systick interrupt is fired to notify user that a tick has passed 
 * Input      : 1- STK_CBF_t CBF
								Describtion: pointer to a function of type STK_CBF_t
								Value      : Address of the Callback function 
 * Output     : void                             */
extern void STK_SetCallBack(STK_CBF_t CBF);

#endif

