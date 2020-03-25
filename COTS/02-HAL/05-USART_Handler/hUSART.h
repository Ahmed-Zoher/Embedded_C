#ifndef hSTK_H
#define hSTK_H

extern void STK_Init(void);
extern void STK_Start(void);
extern void STK_Stop(void);
extern void STK_SetTimeUS(u32 timeUS);
extern void STK_SetCallBack(STK_CBF_t CBF);

#endif

