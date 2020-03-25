#include "STD_TYPES"

#include "DELAY_interface.h"

void delay_ms(u32 value){
    u32 i;
    //u32 count= (value-TM)/T_1loop;
    u32 count= (100-5)/20;
    for(i;i<100;i++){
        asm("NOP");
}