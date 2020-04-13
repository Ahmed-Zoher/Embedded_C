/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#ifndef dSCHEDULER_H
#define dSCHEDULER_H

/*************************************************/
/****** Definitions & Static Configurations ******/
/*************************************************/

#define STATE_SUSPENDED   0
#define STATE_RUNNING     1
#define STATE_PAUSED      2   /*check on it later (NOT IMPLEMENTED YET)*/


/*************************************************/
/******** UserDefined Types Declarations *********/
/*************************************************/

typedef void(*TaskRunnable_t)(void);

typedef struct{
    TaskRunnable_t Runnable    ;
    u32            PeriodicityUS ;
    u8*            TaskName;
}Task_t;

typedef struct {
    const Task_t * const Task;
    u32     FirstDelayInTicks;
}SysTaskInfo_t;


/*************************************************/
/********** Public Function Prototypes ***********/
/*************************************************/

/* Description: This API shall do the following:  
									1- Initialize Systasks array   
									2- Initialize Systick Timer
									3- Set Systick Callback Function
									4- Set Systick Time Function
 * Input      : void                                           
 * Output     : void                             */
extern void Scheduler_Init(void);

/* Description: This API shall do the following:
									1- Start The Systick Timer
									2- Enter in an infinite loop and check on OS flag
 * Input      : void                                           
 * Output     : void                             */
extern void Scheduler_Start(void);

/* Description: This API shall Suspend a running task 
 * Input      : 1- u8* name 
								Description: represents the task name given by user
								Value      : a string containing task name for example: "FirstTask" 
 * Output     : void                             */
extern void Scheduler_Suspend(u8 * name);

#endif
