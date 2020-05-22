#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "Delay.h"



#define TM (0.00630044444f)
//#define TM (0.634125f)
#define T1 (0.00012594444f)

//#define T1 (0.00539875f)
//#define T1 (0.0002630152f)
//#define TM (0.634125f)
//#define TM (6.34125f)
/*loop time (T1)=5.39875 us*/
/*calculation time (T2)=627.875 us*/
/*context switching time (T3)=3.995 us*/
/*context switching time (T4)=2.255 us*/
void _delay_ms(u32 Val)
{
  u32 i;
u32 count =   (u32)((float)Val-TM)/(T1*3);
for (i=0;i<count;i++)
{
  asm("NOP");
}
}
