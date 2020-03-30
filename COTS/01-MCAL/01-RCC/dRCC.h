/********************************************/
/*Author	:	AHMED ZOHER	& WALEED ADEL   */
/*Version	: 	V01				            */
/*Date		:	14 Jan 2020		            */
/********************************************/

#ifndef dRCC_H
#define dRCC_H

#define OK                  0
#define NOK                 1

//TODO : add prefix

#define HSI                 0
#define HSE                 1
#define PLL                 2
#define SYS_CLK             3


#define HSION_MASK          (0x1)
#define HSIRDY_MASK         (0x2)
#define HSEON_MASK          (0x10000)
#define HSERDY_MASK         (0x20000)
#define PLLON_MASK          (0x1000000)
#define PLLRDY_MASK         (0x2000000)
#define SWS_MASK            (0xC)
#define SWS_OFFSET          (2)


#define MCO_SYSCLK          (4)
#define MCO_HSI             (5)
#define MCO_HSE             (6)
#define MCO_PLL             (7)
#define MCO_MASK            (0x7000000)
#define MCO_CLEAR_MASK      (0xF8FFFFFF)


#define OFF                 0
#define ON                  1


#define AHB                 0
#define APB1                1
#define APB2                2


#define GPIO_A_MASK         (0x4)
#define GPIO_B_MASK         (0x8)
#define GPIO_C_MASK         (0x10)


#define HPRE_CLEAR_MASK      (0x0F)

#define PLLSRC_HSE_MASK      (0x00010000)
#define PLLSRC_HSI_DIV2_MASK (0x00000000)
#define PLLSRC_CLEAR_MASK    (0xFFFEFFFF)
#define PLLXTPRE_CLEAR_MASK  (0xFFFDFFFF)
#define PLLXTPRE_MASK        (0x00020000)
#define PLLMUL_2             (0x000000)
#define PLLMUL_3             (0x040000)
#define PLLMUL_4             (0x080000)
#define PLLMUL_5             (0x0C0000)
#define PLLMUL_6             (0x100000)
#define PLLMUL_7             (0x140000)
#define PLLMUL_8             (0x180000)
#define PLLMUL_9             (0x1C0000)
#define PLLMUL_10            (0x200000)
#define PLLMUL_11            (0x240000)
#define PLLMUL_12            (0x280000)
#define PLLMUL_13            (0x2C0000)
#define PLLMUL_14            (0x300000)
#define PLLMUL_15            (0x340000)
#define PLLMUL_16            (0x380000)
#define PLLMUL_MASK          (0x3C0000)


/*The Prephirals Masks of AHB Bus */
#define DMA1EN            (0x1)
#define DMA2EN            (0x2)
#define SRAMEN            (0x4)
#define FLITFEN           (0x10)
#define CRCEN             (0x40)
#define FSMCEN            (0x100)
#define SDIOEN            (0x400)


/*The Prephirals Masks of APB1 Bus */
#define TIM2EN            (0x1)
#define TIM3EN            (0x2)
#define TIM4EN            (0x4)
#define TIM5EN            (0x8)
#define TIM6EN            (0x10)
#define TIM7EN            (0x20)
#define TIM12EN           (0x40)
#define TIM13EN           (0x80)
#define TIM14EN           (0x100)
#define WWDGEN            (0x800)
#define SPI2EN            (0x4000)
#define SPI3EN            (0x8000)
#define USART2EN          (0x20000)
#define USART3EN          (0x40000)
#define USART4EN          (0x80000)
#define USART5EN          (0x100000)
#define I2C1EN            (0x200000)
#define I2C2EN            (0x400000)
#define USBEN             (0x800000)
#define CANEN             (0x2000000)
#define BKPEN             (0x8000000)
#define PWREN             (0x10000000)
#define DACEN             (0x20000000)


/*The Prephirals Masks of APB2 Bus */
#define AFIOEN            (0x1)
#define IOPAEN            (0x4)
#define IOPBEN            (0x8)
#define IOPCEN            (0x10)
#define IOPDEN            (0x20)
#define IOPEEN            (0x40)
#define IOPFEN            (0x80)
#define IOPGEN            (0x100)
#define ADC1EN            (0x200)
#define ADC2EN            (0x400)
#define TIM1EN            (0x800)
#define SPI1EN            (0x1000)
#define TIM8EN            (0x2000)
#define USART1EN          (0x4000)
#define ADC3EN            (0x8000)
#define TIM9EN            (0x80000)
#define TIM10EN           (0x100000)
#define TIM11EN           (0x200000)


/*This Defines HSITRIM masks*/
#define HSITRIM_MASK               0xFFFFFF07
#define HSITRIM_TRIM_0_VALUE       0x00000000
#define HSITRIM_TRIM_1_VALUE       0x00000008
#define HSITRIM_TRIM_2_VALUE       0x00000010
#define HSITRIM_TRIM_3_VALUE       0x00000018
#define HSITRIM_TRIM_4_VALUE       0x00000020
#define HSITRIM_TRIM_5_VALUE       0x00000028
#define HSITRIM_TRIM_6_VALUE       0x00000030
#define HSITRIM_TRIM_7_VALUE       0x00000038
#define HSITRIM_TRIM_8_VALUE       0x00000040
#define HSITRIM_TRIM_9_VALUE       0x00000048
#define HSITRIM_TRIM_10_VALUE      0x00000050
#define HSITRIM_TRIM_11_VALUE      0x00000058
#define HSITRIM_TRIM_12_VALUE      0x00000060
#define HSITRIM_TRIM_13_VALUE      0x00000068
#define HSITRIM_TRIM_14_VALUE      0x00000070
#define HSITRIM_TRIM_15_VALUE      0x00000078
#define HSITRIM_TRIM_16_VALUE      0x00000080
#define HSITRIM_TRIM_17_VALUE      0x00000088
#define HSITRIM_TRIM_18_VALUE      0x00000090
#define HSITRIM_TRIM_19_VALUE      0x00000098
#define HSITRIM_TRIM_20_VALUE      0x000000A0
#define HSITRIM_TRIM_21_VALUE      0x000000A8
#define HSITRIM_TRIM_22_VALUE      0x000000B0
#define HSITRIM_TRIM_23_VALUE      0x000000B8
#define HSITRIM_TRIM_24_VALUE      0x000000C0
#define HSITRIM_TRIM_25_VALUE      0x000000C8
#define HSITRIM_TRIM_26_VALUE      0x000000D0
#define HSITRIM_TRIM_27_VALUE      0x000000D8
#define HSITRIM_TRIM_28_VALUE      0x000000E0
#define HSITRIM_TRIM_29_VALUE      0x000000E8
#define HSITRIM_TRIM_30_VALUE      0x000000F0
#define HSITRIM_TRIM_31_VALUE      0x000000F8


u8 Rcc_GetBusPrescaler(u8 Bus);
u8 RCC_GetSystemClockFreq(void);


/* Description: This API shall Set the Clock to be ON or OFF*/
/* Input  => Clock {HSION_MASK, HSEON_MASK,                 */
/*                              PLLON_MASK}                 */
/*        => State { ON, OFF}                               */
/* Output => {OK, NOK}                                      */
u8 RCC_SetClockState(u32 Clock, u8 State);


/* Description: This API shall Read the Clock State         */
/* Input  => Clock {HSI, HSE, PLL}                          */
/* Output => Clock State {1 for ON, 0 for OFF}              */
u8 RCC_GetClockState(u32 Clock);


/* Description: This API shall Set the System Clock         */
/* Input  => Clock {HSI, HSE, PLL}                          */
/* Output => {OK, NOK}                                      */
u8 RCC_SetSystemClock(u8 Clock);


/* Description: This API shall Get the System Clock state   */
/* Input  => void                                           */
/* Output => System Clock State {1 for ON, 0 for OFF}       */
u8 RCC_GetSystemClock(void);


/* Description: This API shall Output the Clock on MCO Pin  */
/* Input  => Clock {HSI, HSE, PLL, SYS_CLK}                 */
/* Output => {OK, NOK}                                      */
u8 RCC_ConfigureMCO(u8 Clock);


/* Description: This API shall set PLL source & Multiplier  */
/* Input  => Pll_Src {PLLSRC_HSI/2_MASK, PLLSRC_HSE_MASK}   */
/*        => Pll_Mul {PLLMUL_2, PLLMUL_3, ... , PLLMUL_16}  */
/* Output => {OK, NOK}                                      */
u8 RCC_ConfigurePLL(u32 Pll_Src, u32 Pll_Mul);


/* Description: This API shall Output the Clock on MCO Pin  */
/* Input  => Bus {AHB, APB1, APB2}                          */
/*        => Peripheral {GPIO_A_MASK, GPIO_B_MASK,          */
/*                       GPIO_C_MASK}                       */
/*        => State {1 for ON, 0 for OFF}                    */
/* Output => {OK, NOK}                                      */
u8 RCC_SetPrephiralClockState(u8 Bus, u32 Prephiral, u8 State);


#endif
