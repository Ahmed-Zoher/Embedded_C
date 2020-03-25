#ifndef dSTK_H
#define dSTK_H

#define CLOCK_PRE_AHB_DIV8    0
#define CLOCK_PRE_AHB         1


typedef void(*STK_CBF_t)(void);

extern void STK_MCAL_Init(void);
extern void STK_MCAL_Start(void);
extern void STK_MCAL_Stop(void);
extern void STK_MCAL_SetTimeUS(u32 timeUS, u8 AHB_Clock_Hz);
extern void STK_MCAL_SetCallBack(STK_CBF_t CBF);

#endif

