/********************************************/
/*Author	:	AHMED ZOHER	& WALEED ADEL   */
/*Version	: 	V01				            */
/*Date		:	14 Jan 2020		            */
/********************************************/
#include "STD_TYPES.h"
#include <dNVIC.h>





#define NVIC_REGS_WIDTH    32 


/* Description: This API shall Enable an IRQ#                  */
/* Input  => Clock {InterruptID_0, InterruptID_1,            } */
/* Output => {OK, NOK}                                         */
void NVIC_EnableIRQ(u8 InterruptID){
    u8 regNum = InterruptID / NVIC_REGS_WIDTH ;
    u32 bitIdx = InterruptID % NVIC_REGS_WIDTH ;
    NVIC_SETENA[regNum] = 1 << bitIdx ;
}

/* Description: This API shall Disable an IRQ#                 */
/* Input  => Clock {InterruptID_0, InterruptID_1,            } */
/* Output => {OK, NOK}                                         */
void NVIC_DisableIRQ(u8 InterruptID){
    u8 regNum = InterruptID / NVIC_REGS_WIDTH ;
    u32 bitIdx = InterruptID % NVIC_REGS_WIDTH ;
    NVIC_CLRENA[regNum] = 1 << bitIdx ;
}

/* Description: This API shall Set an IRQ# Pending Status     */
/* Input  => Clock {InterruptID_0, InterruptID_1,            }*/
/* Output => {OK, NOK}                                        */
void NVIC_SetPendingIRQ(u8 InterruptID){
    u8 regNum = InterruptID / NVIC_REGS_WIDTH ;
    u32 bitIdx = InterruptID % NVIC_REGS_WIDTH ;
    NVIC_SETPEND[regNum] = 1 << bitIdx ;
}

/* Description: This API shall Clear an IRQ# Pending Status   */
/* Input  => Clock {InterruptID_0, InterruptID_1,            }*/
/* Output => {OK, NOK}                                        */
void NVIC_ClearPendingIRQ(u8 InterruptID){
    u8 regNum = InterruptID / NVIC_REGS_WIDTH ;
    u32 bitIdx = InterruptID % NVIC_REGS_WIDTH ;
    NVIC_CLRPEND[regNum] = 1 << bitIdx ;
}

/* Description: This API shall Get an IRQ# Pending Status     */
/* Input  => Clock {InterruptID_0, InterruptID_1,            }*/
/*        => PendingState Pointer to assign the return to it  */
/* Output => {OK, NOK}                                        */
void NVIC_GetPendingState(u8 InterruptID, void * PendingState){
    u8 regNum = InterruptID / NVIC_REGS_WIDTH ;
    u32 bitIdx = InterruptID % NVIC_REGS_WIDTH ;
    * (u8*)PendingState =(NVIC_CLRPEND[regNum] >> bitIdx)&0x1 ;
}

/* Description: This API shall Set the IRQs PriorityGrouping  */
/* Input  => Clock {NVIC_GROUP16_SUBGROUP0,                  }*/
/* Output => {OK, NOK}                                        */
void SCB_SetPriorityGrouping(u32 NVIC_GROUP){
    SCB_AIRCR  = SCB_AIRCR_KEY;
    SCB_AIRCR |= NVIC_GROUP;
}

/* Description: This API shall Enable all IRQs                  */
/* Input  => void                                             } */
/* Output => {OK, NOK}                                          */
void NVIC_EnableAllIRQs(void){
    __asm__("MOV  R4, #0");
    __asm__("MSR  PRIMASK,  R4");
}

/* Description: This API shall Disable all IRQs                 */
/* Input  => void                                             } */
/* Output => {OK, NOK}                                          */
void NVIC_DisableAllIRQs(void){
    __asm__("MOV   R4, #1");
    __asm__("MSR  PRIMASK,  R4");
}

/* Description: This API shall Enable all Faults                */
/* Input  => void                                             } */
/* Output => {OK, NOK}                                          */
void NVIC_EnableFaults(void){
    __asm__("MOV   R4, #0");
    __asm__("MSR  FAULTMASK,  R4");
}

/* Description: This API shall Disable all Faults                */
/* Input  => void                                              } */
/* Output => {OK, NOK}                                           */
void NVIC_DisableFaults(void){
    __asm__("MOV   R4, #1");
    __asm__("MSR  FAULTMASK,  R4");
}

/* Description: This API shall Set priority bounds              */
/* Input  => Priority {0,1,2      }                             */
/* Output => {OK, NOK}                                          */
void NVIC_SetPriorityFilter(u8 Priority){
    __asm__("LSLS R0, R0, #4");
    __asm__("MSR  BASEPRI,  R0");
}

/* Description: This API shall Clear priority bounds            */
/* Input  => void                                             } */
/* Output => {OK, NOK}                                          */
void NVIC_ClearPriorityFilter(void){
    __asm__("MOV   R4, #0");
    __asm__("MSR  BASEPRI,  R4");
}


void NVIC_GenerateSoftwareIRQ(u8 InterruptID){
    NVIC_INTID = InterruptID;
}


void NVIC_SetPriority(u8 InterruptID, u8 Priority){
    NVIC_IP[InterruptID] = Priority;
    //u8 Local_Grouping = (SCB_AIRCR & SCB_AIRCR_PRI_GROUP_MASK ) >> SCB_AIRCR_PRI_GROUP_SHIFT ; 
    //Copy_InterruptID |= ((Copy_Preemption << (Local_Grouping - SCB_AIRCR_PRI_GROUP_HABD3)) | Copy_SubGroup );
}

void NVIC_GetPriority(u8 InterruptID, u8 * Priority){
    *Priority = NVIC_IP[InterruptID];
    //u8 Local_Grouping = (SCB_AIRCR & SCB_AIRCR_PRI_GROUP_MASK ) >> SCB_AIRCR_PRI_GROUP_SHIFT ;
    //* Copy_Preemption = (Copy_InterruptID >> (Local_Grouping + SCB_AIRCR_PRI_GROUP_HABD1));
    //* Copy_SubGroup   = ((Copy_InterruptID << (SCB_AIRCR_PRI_GROUP_HABD7 - Local_Grouping )) >> (SCB_AIRCR_PRI_GROUP_HABD11 - Local_Grouping));
}
