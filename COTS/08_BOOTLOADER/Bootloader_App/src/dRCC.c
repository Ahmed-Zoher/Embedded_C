/********************************/
/*Author	:	AHMED ZOHER	    */
/*Version	: 	V01				*/
/*Date		:	14 Jan 2020		*/
/********************************/
#include "STD_TYPES.h"
#include <dRCC.h>







#define  SW_CLEAR_MASK       (0xfffffffc)
#define  PLLMUL_CLEAR_MASK   (0xFFFF7FFF)
#define  RCC_BASE_ADDRESS    (const)0x40021000

typedef struct
{
    u32 RCC_CR      ;
    u32 RCC_CFGR    ;
    u32 RCC_CIR     ;
    u32 RCC_APB2RSTR;
    u32 RCC_APB1RSTR;
    u32 RCC_AHBENR  ;
    u32 RCC_APB2ENR ;
    u32 RCC_APB1ENR ;
    u32 RCC_BDCR    ;
    u32 RCC_CSR     ;
}RCC_Reg;

#define RCC  ((volatile RCC_Reg *)RCC_BASE_ADDRESS)



/**************************************************/
/**********PRIVATE FUNCTIONS DELCARARTIONS*********/
/**************************************************/
static u8 RCC_GetAHB_PreScaler(void);
static u8 RCC_GetPLL_Freq(void);
static u8 RCC_GetPLL_PreScaler(void);



/**************************************************/
/***************FUNCTIONS DEFINITION***************/
/**************************************************/

/* Description: This API shall Set the Clock to be ON or OFF*/
/* Input  => Clock {HSION_MASK, HSEON_MASK,                 */
/*                              PLLON_MASK}                 */
/*        => State { ON, OFF}                               */
/* Output => void                                           */
u8 RCC_SetClockState(u32 Clock, u8 State){
    u8 status           = NOK;
    switch (State){
        case ON:
            RCC->RCC_CR |= Clock;
            status       = OK;
        break;
        case OFF:
            RCC->RCC_CR &= (~(Clock));
            status       = OK;
        break;
    }
    return status;
}


/* Description: This API shall Read the Clock State         */
/* Input  => Clock {HSIRDY_MASK, HSERDY_MASK,               */
/*                              PLLRDY_MASK}                */
/* Output => Clock State {1 for ON, 0 for OFF}              */
u8 RCC_GetClockState(u32 Clock){

/*    
    if(RCC->RCC_CR & Clock){
        
        return ON;
    }else{
        return OFF;
    }
  */  
    
   return ((RCC->RCC_CR & Clock) >> Clock); 
}


/* Description: This API shall Set the System Clock         */
/* Input  => Clock {HSI, HSE, PLL}                          */
/* Output => {OK, NOK}                                      */
u8 RCC_SetSystemClock(u8 Clock){
    u32 local     ;
    local          = RCC->RCC_CFGR;
    local         &= SW_CLEAR_MASK;
    local         |= Clock;
    RCC->RCC_CFGR    = local;
    return OK;
}


/* Description: This API shall Get the System Clock         */
/* Input  => void                                           */
/* Output => System Clock {HSE 01, HSI 00, PLL  10}         */
u8 RCC_GetSystemClock(void){
	u8 SW = (RCC->RCC_CFGR & 0x3);
    return SW;
}


/* Description: This API shall Get the System Clock         */
/* Input  => void                                           */
/* Output => System Clock Frequency in Hz                   */
u8 RCC_GetSystemClockFreq(void){
    u8 freq;
    u8 Clock = RCC_GetSystemClock();
    switch(Clock){
        case HSE:freq=8;break;
        case HSI:freq=8;break;
        case PLL:freq=RCC_GetPLL_Freq();break;
    }
    u8 sysclock_prescaler = RCC_GetAHB_PreScaler();
    return (freq/sysclock_prescaler); 
}


static u8 RCC_GetAHB_PreScaler(void){
    u32 AHB_PreScaler = 0;
    u32 SYSCLK_DIV_PRESCALAR = (RCC->RCC_CFGR &~ HPRE_CLEAR_MASK) >> 4;
    switch (SYSCLK_DIV_PRESCALAR){
        case 0b1000 : AHB_PreScaler = 2  ; break;
        case 0b1001 : AHB_PreScaler = 4  ; break;
        case 0b1010 : AHB_PreScaler = 8  ; break;
        case 0b1011 : AHB_PreScaler = 16 ; break;
        case 0b1100 : AHB_PreScaler = 64 ; break;
        case 0b1101 : AHB_PreScaler = 128; break;
        case 0b1110 : AHB_PreScaler = 256; break;
        case 0b1111 : AHB_PreScaler = 512; break;
        default     : AHB_PreScaler = 1  ; break;
    }
    return AHB_PreScaler;
}


static u8 RCC_GetPLL_Freq(void){
    u8 pll_value;
    u32 pll_src = RCC->RCC_CFGR & ~PLLSRC_CLEAR_MASK;
    if (pll_src == PLLSRC_HSE_MASK){
            u32 PLLXTPRE = RCC->RCC_CFGR & ~PLLXTPRE_MASK;
        if(PLLXTPRE == PLLXTPRE_MASK){
            pll_value=4; // HSE /2
        }else{
            pll_value=8; // HSE
        }
    }else{
        pll_value=4; //HSI/2
    }
    u8 pll_prescaler = RCC_GetPLL_PreScaler();
    return (pll_value*pll_prescaler);
}


static u8 RCC_GetPLL_PreScaler(void){
    u32 prescaler = (RCC->RCC_CFGR & PLLMUL_MASK)>> 18;
    if (prescaler>14){
        prescaler = 16;
    }else{
        prescaler += 2;
    }
    return prescaler;
}

u8 Rcc_GetBusPrescaler(u8 Bus){
	u8 local;
	switch(Bus){
	case 1:
		local = (RCC->RCC_CFGR & ((u32)0x700))>> 8;
		break;
	case 2:
		local = (RCC->RCC_CFGR & ((u32)0x3800))>> 11;
		break;
	}
	/* get prescaler of bus */
	switch (local){
		case 4: return 2   ;break;
		case 5:  return 4  ;break;
		case 6: return 8   ;break;
		case 7:  return 16  ;break;
		default: return 1   ;break;

	}
}

/* Description: This API shall Output the Clock on MCO Pin  */
/* Input  => Clock {MCO_HSI, MCO_HSE, MCO_PLL, MCO_SYSCLK}  */
/* Output => {OK, NOK}                                      */
u8 RCC_ConfigureMCO(u8 Clock){
    RCC->RCC_CFGR &= (MCO_CLEAR_MASK);
    RCC->RCC_CFGR |= Clock;
    return OK;
}


/* Description: This API shall set PLL source & Multiplier  */
/* Input  => Pll_Src {PLLSRC_HSI_DIV2_MASK, PLLSRC_HSE_MASK}*/
/*        => Pll_Mul {PLLMUL_2, PLLMUL_3, ... , PLLMUL_16}  */
/* Output => {OK, NOK}                                      */
u8 RCC_ConfigurePLL(u32 Pll_Src, u32 Pll_Mul){
    u32 local      = 0;
    local          = RCC->RCC_CFGR;
    local         &= PLLMUL_CLEAR_MASK;
    local         |= Pll_Mul;
    local &= PLLSRC_CLEAR_MASK;
    local |= Pll_Src;
    RCC->RCC_CFGR  = local;
    return OK;
}


/* Description: This API shall Output the Clock on MCO Pin  */
/* Input  => Bus {AHB, APB1, APB2}                          */
/*        => Peripheral {GPIO_A_MASK, GPIO_B_MASK,          */
/*                       GPIO_C_MASK}                       */
/*        => State {1 for ON, 0 for OFF}                    */
/* Output => {OK, NOK}                                      */
u8 RCC_SetPrephiralClockState(u8 Bus, u32 Prephiral, u8 State){
        switch (Bus){
        case AHB:
                switch (State){
                    case ON:
                        RCC->RCC_AHBENR |= Prephiral;
                    break;
                    case OFF:
                        RCC->RCC_AHBENR &= (~(Prephiral));
                    break;
                }
        break;
        case APB1:
                switch (State){
                    case ON:
                        RCC->RCC_APB1ENR |= Prephiral;
                    break;
                    case OFF:
                        RCC->RCC_APB1ENR &= (~(Prephiral));
                    break;
                }
        break;
        case APB2:
                switch (State){
                    case ON:
                        RCC->RCC_APB2ENR |= Prephiral;
                    break;
                    case OFF:
                        RCC->RCC_APB2ENR &= (~(Prephiral));
                    break;
                }
        break;
    }
    return OK;
}
