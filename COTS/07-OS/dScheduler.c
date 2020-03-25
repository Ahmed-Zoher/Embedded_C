#include "STD_TYPES.h"
#include <dScheduler.h>
#include <dScheduler_Config .h>
#include <dSTK.h>
#include <hSTK.h>
#include <lString.h>


u8 OS_Flag = 0;

extern SysTaskInfo_t SysTasksInfo[NUM_OF_TASKS];

typedef struct{
    SysTaskInfo_t * TaskInfo;
    u32             TicksToExecute;
    u32             PeriodInTicks;
    u8              State;
}SysTask_t;


SysTask_t SysTasks[NUM_OF_TASKS];

static void Scheduler_SetOS_Flag (void);
static void Scheduler (void);


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
    /*Set Sysytick Callback Function*/
     STK_MCAL_SetCallBack(Scheduler_SetOS_Flag);
    /*Set Sysytick Time Function*/
     STK_SetTimeUS(TICK_TIME_US);
}


void Scheduler_SetOS_Flag (void){
    OS_Flag = 1;
}


void Scheduler_Start (void){
    STK_MCAL_Start();
    while (1){
        if (OS_Flag){
        OS_Flag = 0;
        Scheduler();
        }
    }
}


void Scheduler (void){
    for (u8 Loop_Counter = 0; Loop_Counter < NUM_OF_TASKS ; Loop_Counter++){
        if (SysTasks[Loop_Counter].TicksToExecute == 0 && SysTasks[Loop_Counter].State == STATE_RUNNING ){
            SysTasks[Loop_Counter].TaskInfo -> Task -> Runnable();
            SysTasks[Loop_Counter].TicksToExecute = SysTasks[Loop_Counter].PeriodInTicks;
        }
        SysTasks[Loop_Counter].TicksToExecute-- ;
    }
}


void Scheduler_Suspend (u8* name){
    for (u8 Loop_Counter = 0; Loop_Counter < NUM_OF_TASKS ; Loop_Counter++){
      if (String_Compare(SysTasks[Loop_Counter].TaskInfo -> Task -> TaskName,name) == 1){
        SysTasks[Loop_Counter].State = STATE_SUSPENDED;
      }
    }
}


