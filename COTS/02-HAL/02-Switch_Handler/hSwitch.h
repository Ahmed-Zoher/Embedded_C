#ifndef HSWITCH_H
#define HSWITCH_H






#define Switch_1         0
#define Switch_2         1
#define Switch_Flash     2

#define DEBOUNCE_DELAY_MS      50

#define SWITCH_OS_MODE_DISABLE 1 
#define SWITCH_OS_MODE_ENABLE  0
#define SWITCH_OS_MODE         SWITCH_OS_MODE_DISABLE

typedef struct{
    u8         SwitchName  ;
    u16        Pin         ;
    u8         PullState   ;
    PORT_REG*  Port        ;
}Switch_MAP_t;


void hSwitch_Init(void);
u8 hSwitch_GetSwitchState(u8 L_SwitchName);

#endif 