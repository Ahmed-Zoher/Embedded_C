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

	/* RCC INIT */
	RCC_Init();

	/* Enable Clock on Port C */
	RCC_EnablePrephiralClock(2,4);
	RCC_EnablePrephiralClock(2,2);

	/* Set Pin C14 Mode to Output Push Pull */
	DIO_SetPinMode ('C', 15, 0b0010);
	DIO_SetPinValue('C',15,0);

	DIO_SetPinMode ('A', 7, 0b0010);
	DIO_SetPinValue('A',7,0);


    /* Set Pin C13 Mode to Output Push Pull */

	DIO_SetPinMode ('A', 0 , 0b1000);
	DIO_SetPinValue('A',0,1);

	DIO_SetPinMode ('A', 1 , 0b1000);
	DIO_SetPinValue('A',1,1);

	DIO_SetPinMode ('A', 2 , 0b1000);
	DIO_SetPinValue('A',2,1);

	DIO_SetPinMode ('A', 3 , 0b1000);
	DIO_SetPinValue('A',3,1);

	DIO_SetPinMode ('A', 4 , 0b1000);
	DIO_SetPinValue('A',4,1);

	DIO_SetPinMode ('A', 5 , 0b1000);
	DIO_SetPinValue('A',5,1);

	DIO_SetPinMode ('A', 6 , 0b1000);
	DIO_SetPinValue('A',6,1);

	//DIO_SetPinMode ('A', 7 , 0b1000);
	//DIO_SetPinValue('A',7,0);


while(1){
	DIO_SetPinValue('A',7,0);
	DIO_SetPinValue('C',15,0);
	if (DIO_GetPinValue('A',0)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<20000;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<20000;o++)
		p=p+1;
		//  delay end
		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}
	if (DIO_GetPinValue('A',1)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<100;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<100;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}

	if (DIO_GetPinValue('A',2)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<120;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<120;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}

	if (DIO_GetPinValue('A',3)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<140;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<140;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}

	if (DIO_GetPinValue('A',4)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<70;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<70;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}

	if (DIO_GetPinValue('A',5)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<220;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<220;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}
	if (DIO_GetPinValue('A',6)==0){
		DIO_SetPinValue('A',7,1);
		DIO_SetPinValue('C',15,1);
	//	DIO_SetPinValue('A',7,1);

	    //  delay start
	    u8 p=0;
		for (u32 o=0;o<50;o++)
		p=p+1;
		p=0;
		for (u32 o=0;o<50;o++)
		p=p+1;
		//  delay end

		DIO_SetPinValue('A',7,0);
		DIO_SetPinValue('C',15,0);
	}


}

}
