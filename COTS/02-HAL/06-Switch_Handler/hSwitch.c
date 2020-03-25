#include "STD_TYPES.h"
#include "GPIO.h"
#include <hSwitch.h>



typedef struct{
    u8  SwitchName     ;
    u8  PrevState      ;
    u8  State          ;
    u8  DebounceCounter;
}Switch_t;

Switch_t SwitchesStates[NUM_OF_SWITCHES];
extern Switch_MAP_t  map[NUM_OF_SWITCHES];
extern GPIO_t Switches[NUM_OF_SWITCHES];


void hSwitch_Init(void){
    for (u8 LoopCounter = 0 ; LoopCounter < NUM_OF_SWITCHES ; LoopCounter++){
        GPIO_voidSetPinMode(&Switches[LoopCounter]);
        GPIO_voidSetPinValue(map[LoopCounter].Port,Switches[LoopCounter].GPIO_u16Pin,map[LoopCounter].PullState);
        SwitchesStates[LoopCounter].SwitchName = map[LoopCounter].SwitchName ;
    }
}

u8 hSwitch_GetSwitchState(u8 L_SwitchName){
    return SwitchesStates[L_SwitchName].State;
}

void hSwitch_DebounceTask(void){
    for (u8 LoopCounter = 0; LoopCounter < NUM_OF_SWITCHES ;LoopCounter++){
        u8 CurrentState = GPIO_u8GetPinValue(Switches[LoopCounter].GPIO_ptrPort,map[LoopCounter].Pin);
        if (CurrentState == SwitchesStates[LoopCounter].PrevState)
            SwitchesStates[LoopCounter].DebounceCounter++;
        else 
            SwitchesStates[LoopCounter].DebounceCounter = 0;
    
        if (SwitchesStates[LoopCounter].DebounceCounter == 5){
            SwitchesStates[LoopCounter].State = CurrentState;
            SwitchesStates[LoopCounter].DebounceCounter = 0;
        }
        SwitchesStates[LoopCounter].PrevState = CurrentState;
    }
}
