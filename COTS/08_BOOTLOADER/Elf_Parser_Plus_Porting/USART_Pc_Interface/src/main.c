
#include "STD_TYPES.h"
#include <dRCC.h>

#include "dGPIO.h"

#include "dNVIC.h"

#include "hUSART.h"


USART_InitTypeDef init_struct;
u8 dataRec [3];
u8 dataTr  [3]={1,2,3};

void Recieved(void){
	trace_printf("ana 5lst recieving/////////////////////////////////////////// \n");
	for (u8 i=0;i<3;i++){
		trace_printf("ana est2belt: %d \n",dataRec[i]); /////////mashkok feha
	}
	hUSART_Receive(USART1,dataRec, 3);
}

void Transmitted(void){
    trace_printf("ana ba3at ////////////////////////////////////////////// \n");
}

int main(void)
{
	RCC_SetClockState(HSION_MASK,ON);
	RCC_SetSystemClock(HSI);

	RCC_SetPrephiralClockState(APB2,IOPAEN,ON);

	hUSART_StructDefaultInit(&init_struct);
	//hUSART_SetTxCallBackFn(USART1,Transmitted);
	hUSART_SetRxCallBackFn(USART1,Recieved);
	hUSART_Init(USART1, &init_struct);
	hUSART_Receive(USART1,dataRec, 3);

	//hUSART_Send(USART1,dataTr,3);

	while (1)
	{

	}
	return 0;
}
