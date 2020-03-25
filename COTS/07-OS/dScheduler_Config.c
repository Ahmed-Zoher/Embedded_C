#include "STD_TYPES.h"
#include <dScheduler.h>
#include <dScheduler_Config .h>


extern Task_t switch_task;

extern void hSwitch_DebounceTask(void);
extern void hLcd_Task(void);

Task_t Lcd_task = {.Runnable=&hLcd_Task, .PeriodicityUS = 5000, .TaskName = "LcdTask"};
Task_t Switch_task = {.Runnable=&hSwitch_DebounceTask, .PeriodicityUS = 5000, .TaskName = "SwitchDebounce"};

SysTaskInfo_t SysTasksInfo [NUM_OF_TASKS] ={{ .Task = &Lcd_task, .FirstDelayInTicks = 0}};
