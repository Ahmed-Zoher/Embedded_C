#ifndef HSWITCH_H
#define HSWITCH_H




#define PULL_UP          1
#define PULL_DOWN        0

#define Switch_1         0
#define Switch_2         1



typedef struct{
    u8         SwitchName  ;
    u16        Pin         ;
    u8         PullState   ;
    PORT_REG*  Port        ;
}Switch_MAP_t;


void hSwitch_Init(void);
u8 hSwitch_GetSwitchState(u8 L_SwitchName);

#endif 