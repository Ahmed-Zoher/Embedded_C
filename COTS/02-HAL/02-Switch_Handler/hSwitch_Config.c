#include "STD_TYPES.h"
#include "GPIO.h"
#include <hSwitch.h>

#define NUM_OF_SWITCHES  2

const Switch_MAP_t  map[NUM_OF_SWITCHES]={{Switch_1     ,GPIO_PIN15,PULL_UP,GPIO_PORTC}
                                         ,{Switch_2     ,GPIO_PIN14,PULL_DOWN,GPIO_PORTC}};


const GPIO_t Switches[NUM_OF_SWITCHES] = {{GPIO_PIN15_MASK,INPUT_PULL_UP_DOWN,GPIO_PORTC}
		                                 ,{GPIO_PIN14_MASK,INPUT_PULL_UP_DOWN,GPIO_PORTC}};
