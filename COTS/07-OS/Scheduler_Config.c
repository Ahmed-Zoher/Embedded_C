/************************************************/
/* Author	 :	Ahmed Zoher	& Waleed Adel         */
/* Version : 	V01				                        */
/* Date		 :	March 2020		                    */
/************************************************/

#include "STD_TYPES.h"
#include <dScheduler.h>
#include <dScheduler_Config .h>


/*************************************************/
/********** Extern & Global Variables ************/
/*************************************************/

/* Tasks Created by User in Application Layer */
extern Task_t lcdAPP;

/* Functions/Runnables Present in HAL Modules */
//extern void hSwitch_DebounceTask(void);
extern void hLcd_Task(void);

/* Tasks created for HAL Modules              */
Task_t Lcd_task      = {.Runnable=&hLcd_Task,            .PeriodicityUS = 5000, .TaskName = "LcdTask"};
//Task_t Switch_task = {.Runnable=&hSwitch_DebounceTask, .PeriodicityUS = 5000, .TaskName = "SwitchDebounce"};

/* Array of SysTasksInfo_t */
/* Assign first delay (in ticks) to each task here */
SysTaskInfo_t SysTasksInfo [NUM_OF_TASKS] ={{ .Task = &Lcd_task, .FirstDelayInTicks = 0},
											                      { .Task = &lcdAPP  , .FirstDelayInTicks = 1000}};
 