#include <STD_TYPES.h>
#include "dGPIO.h"
#include <hSwitch.h>


#define NUM_OF_SWITCHES  1

const Switch_MAP_t  map[NUM_OF_SWITCHES] = {{Switch_Flash     ,GPIO_PIN15,PULL_UP,GPIO_PORTC}};


const GPIO_t Switches[NUM_OF_SWITCHES] = {{GPIO_PIN15_MASK,INPUT_PULL_UP_DOWN,GPIO_PORTC}};
