#ifndef dSCHEDULER_H
#define dSCHEDULER_H

#define STATE_SUSPENDED   0
#define STATE_RUNNING     1
#define STATE_PAUSED      2 // check on it later


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

extern void Scheduler_Init(void);
extern void Scheduler_Start(void);
extern void Scheduler_Suspend(u8 * name);

#endif
