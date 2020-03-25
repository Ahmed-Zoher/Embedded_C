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


int main (void){

	u8 switch_state;

	/* RCC INIT */
	RCC_Init();

	/* Enable Clock on Port C */
	RCC_EnablePrephiralClock(2,4);

	/* Set Pin C14 Mode to Output Push Pull */
	DIO_SetPinMode ('C', 14, 0b1000);
	DIO_SetPinValue('C',14,0);

    /* Set Pin C13 Mode to Output Push Pull */
	DIO_SetPinMode ('C', 15, 0b0010);

while(1){
	/* Get reading from C14 */
	switch_state=DIO_GetPinValue('C',14);

	if (switch_state==0){
	DIO_SetPinValue('C',15,0);
	}else{
	DIO_SetPinValue('C',15,1);
	}
}

}
