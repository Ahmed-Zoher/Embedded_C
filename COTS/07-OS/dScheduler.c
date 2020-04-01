/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#include "STD_TYPES.h"
#include <lString.h>
#include <dSTK.h>
#include <hSTK.h>
#include <dScheduler.h>
#include <dScheduler_Config .h>


/*************************************************/
/******** UserDefined Types Declarations *********/
/*************************************************/

typedef struct{
    SysTaskInfo_t * TaskInfo;
    u32             TicksToExecute;
    u32             PeriodInTicks;
    u8              State;
}SysTask_t;


/*************************************************/
/********** Extern & Global Variables ************/
/*************************************************/

extern SysTaskInfo_t SysTasksInfo[NUM_OF_TASKS];

static u8 OS_Flag = 0;
static SysTask_t SysTasks[NUM_OF_TASKS];


/*************************************************/
/********** Static Function Prototypes ***********/
/*************************************************/

/* Description: This function shall be called in Systick Handler to set OS flag 
 * Input      : void                                           
 * Output     : void                             */
static void Scheduler_SetOS_Flag (void);

/* Description: This function is responsible for managing which task is going to be 
 * executed when it should be executed   
 * Input      : void                                           
 * Output     : void                             */
static void Scheduler (void);


/*************************************************/
/********** Public Function Definitions **********/
/*************************************************/

/* Description: This API shall do the following:  
									1- Initialize Systasks array   
									2- Initialize Systick Timer
									3- Set Sysytick Callback Function
									4- Set Sysytick Time Function
 * Input      : void                                           
 * Output     : void                             */
void Scheduler_Init(void){   

   /*Initialize Systasks array*/
    for (u8 Loop_Counter=0 ; Loop_Counter < NUM_OF_TASKS ; Loop_Counter++){
        SysTasks[Loop_Counter].TaskInfo = &SysTasksInfo[Loop_Counter];
        SysTasks[Loop_Counter].TicksToExecute = SysTasksInfo[Loop_Counter].FirstDelayInTicks;
        SysTasks[Loop_Counter].PeriodInTicks = (SysTasksInfo[Loop_Counter].Task -> PeriodicityUS)/TICK_TIME_US;
        SysTasks[Loop_Counter].State = STATE_RUNNING;
    }
    /*Initialize Systick Timer*/
     STK_MCAL_Init();
    /*Set Systick Callback Function*/
     STK_MCAL_SetCallBack(Scheduler_SetOS_Flag);
    /*Set Systick Time Function*/
     STK_SetTimeUS(TICK_TIME_US);
}


/* Description: This API shall do the following:
									1- Start The Systick Timer
									2- Enter in an infinite loop and check on OS flag
 * Input      : void                                           
 * Output     : void                             */
void Scheduler_Start (void){
    STK_MCAL_Start();
    while (1){
        if (OS_Flag){
        OS_Flag = 0;
        Scheduler();
        }
    }
}


/* Description: This API shall Suspend a running task 
 * Input      : 1- u8* name 
								Description: represents the task name given by user
								Value      : a string containing task name for example: "FirstTask" 
 * Output     : void                             */
void Scheduler_Suspend (u8* name){
    for (u8 Loop_Counter = 0; Loop_Counter < NUM_OF_TASKS ; Loop_Counter++){
      if (String_Compare(SysTasks[Loop_Counter].TaskInfo -> Task -> TaskName,name) == 1){
        SysTasks[Loop_Counter].State = STATE_SUSPENDED;
      }
    }
}


/*************************************************/
/********** Static Function Definitions **********/
/*************************************************/

/* Description: This function shall be called in Systick Handler to set OS flag 
 * Input      : void                                           
 * Output     : void                             */
void Scheduler_SetOS_Flag (void){
    OS_Flag = 1;
}


/* Description: This function is responsible for managing which task is going to be 
 * executed when it should be executed   
 * Input      : void                                           
 * Output     : void                             */
void Scheduler (void){
    for (u8 Loop_Counter = 0; Loop_Counter < NUM_OF_TASKS ; Loop_Counter++){
        if (SysTasks[Loop_Counter].TicksToExecute == 0 && SysTasks[Loop_Counter].State == STATE_RUNNING ){
            SysTasks[Loop_Counter].TaskInfo -> Task -> Runnable();
            SysTasks[Loop_Counter].TicksToExecute = SysTasks[Loop_Counter].PeriodInTicks;
        }
        SysTasks[Loop_Counter].TicksToExecute-- ;
    }
}
