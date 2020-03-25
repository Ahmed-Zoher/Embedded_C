/*
 * This file is part of the ÂµOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "DELAY_interface.h"

void delay(void){

}

int main (void){

	u8 switch_state;
	u8 arr[8]={0,0,0,0,0,0,0,0};
	/* RCC INIT */
	RCC_Init();

	/* Enable Clock on Port C */
	RCC_EnablePrephiralClock(2,4);
	RCC_EnablePrephiralClock(2,2);

	/* Set Pin C14 Mode to Output Push Pull */
	DIO_SetPinMode('C', 14, 0b1000);
	DIO_SetPinValue('C',14,0);

    /* Set Pin C13 Mode to Output Push Pull */

	DIO_SetPinMode ('A', 0 , 0b0010);
	DIO_SetPinMode ('A', 1 , 0b0010);
	DIO_SetPinMode ('A', 2 , 0b0010);
	DIO_SetPinMode ('A', 3 , 0b0010);
	DIO_SetPinMode ('A', 4 , 0b0010);
	DIO_SetPinMode ('A', 5 , 0b0010);
	DIO_SetPinMode ('A', 6 , 0b0010);
	DIO_SetPinMode ('A', 7 , 0b0010);

	u8 pilot[8]={0,0,0,0,0,0,0,0};
	u8 check=0;

while(1){

	check=0;

   /* for(int j=0;j<8;j++){
    	pilot[j]=DIO_GetPinValue('C',14);
    	check+=pilot[j];
    }*/

    //if(check==8){
    	for(int k=0;k<8;k++){
    		u8 p=0;
    	    	    		for (u32 o=0;o<30340;o++){
    	    	    			p=p+1;
    	    	    		}
    	    	    			p=0;
    	    	    			for (u32 o=0;o<30340;o++){
    	    	    				p=p+1;
    	    	    			}
    	    	    			p=0;
    	    	    				for (u32 o=0;o<30340;o++){
    	    	    					p=p+1;
    	    	    				}
    	    	arr[k]=DIO_GetPinValue('C',14);

    	    }
   // }

	for (int i=0;i<8;i++){
			DIO_SetPinValue('A',i,arr[i]);
			//DIO_SetPinValue('A',3,1);
	}

/*
     	    	u8 p=0;
    	    		for (u32 o=0;o<20000;o++){
    	    			p=p+1;
    	    		}
    	    			p=0;
    	    			for (u32 o=0;o<20000;o++){
    	    				p=p+1;
    	    			}
    	    			p=0;
    	    				for (u32 o=0;o<20000;o++){
    	    					p=p+1;
    	    				}
 */
}

}
