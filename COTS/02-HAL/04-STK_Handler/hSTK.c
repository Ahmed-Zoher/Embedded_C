#include "STD_TYPES.h"
#include "dRCC.h"
#include "dSTK.h"
#include "hSTK.h"




/*****************************************/
/********* FUNCTION DEFINITIONS **********/
/*****************************************/
void STK_Init(void){
   STK_MCAL_Init();
}


void STK_Start(void){
   STK_MCAL_Start();
}


void STK_Stop(void){
   STK_MCAL_Stop();
}


void STK_SetTimeUS(u32 timeUS){
   u8 freq = RCC_GetSystemClockFreq();
   STK_MCAL_SetTimeUS(timeUS, freq);
}


void STK_SetCallBack(STK_CBF_t CBF){
   STK_MCAL_SetCallBack(CBF);
}

