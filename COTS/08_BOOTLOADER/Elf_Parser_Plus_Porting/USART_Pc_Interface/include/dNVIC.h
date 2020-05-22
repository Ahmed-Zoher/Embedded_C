/********************************************/
/*Author	:	AHMED ZOHER	& WALEED ADEL   */
/*Version	: 	V01				            */
/*Date		:	14 Jan 2020		            */
/********************************************/


#ifndef NVIC_H_
#define NVIC_H_

/*
Set Interrupt Enable registers 
*/
#define NVIC_SETENA         ((volatile u32*)0xE000E100)


/*
Clear interrupt Enable 
*/
#define NVIC_CLRENA         ((volatile u32*)0xE000E180)


/*
Set Pending 
*/
#define NVIC_SETPEND        ((volatile u32*)0xE000E200)


/*
clear Pending 
*/
#define NVIC_CLRPEND         ((volatile u32*)0xE000E280)



/*
interrupt priority level 
*/
#define NVIC_IP              ((volatile u8*)(0xE000E400))



/*
Interrupt Avtive Status register 
*/
#define NVIC_ACTIVE0       *((volatile u32*)0xE000E300)
#define NVIC_ACTIVE1       *((volatile u32*)0xE000E304)
#define NVIC_ACTIVE2       *((volatile u32*)0xE000E308)
#define NVIC_ACTIVE3       *((volatile u32*)0xE000E30C)
#define NVIC_ACTIVE4       *((volatile u32*)0xE000E30F)
#define NVIC_ACTIVE5       *((volatile u32*)0xE000E313)
#define NVIC_ACTIVE6       *((volatile u32*)0xE000E317)
#define NVIC_ACTIVE7       *((volatile u32*)0xE000E31B)


/*
Interrupt Controller Type Register
*/
#define NVIC_INTLNESNUM     *((volatile u32*)0xE000E004)


/*
Software Trigger Interrupt Register
*/
#define NVIC_INTID         *((volatile u32*)0xE000EF00)


/*
*/
#define        SCB_AIRCR                  *((volatile u32*)0xE000ED0C)
#define        SCB_AIRCR_KEY              0x05FA0000
#define        NVIC_GROUP16_SUBGROUP0     0x00000300
#define        NVIC_GROUP8_SUBGROUP2      0x00000400
#define        NVIC_GROUP4_SUBGROUP4      0x00000500
#define        NVIC_GROUP2_SUBGROUP8      0x00000600
#define        NVIC_GROUP0_SUBGROUP16     0x00000700

#define        SCB_AIRCR_PRI_GROUP_MASK   0x00000700
#define        SCB_AIRCR_PRI_GROUP_SHIFT  0x00000008
#define        SCB_AIRCR_PRI_GROUP_HABD1  0x00000001
#define        SCB_AIRCR_PRI_GROUP_HABD3  0x00000003
#define        SCB_AIRCR_PRI_GROUP_HABD7  0x00000007
#define        SCB_AIRCR_PRI_GROUP_HABD11 0x0000000B

/*
Interrupts Priority
*/

#define PRIORITY_0       ((u8)0x00)
#define PRIORITY_1       ((u8)0x10)
#define PRIORITY_2       ((u8)0x20)
#define PRIORITY_3       ((u8)0x30)
#define PRIORITY_4       ((u8)0x40)
#define PRIORITY_5       ((u8)0x50)
#define PRIORITY_6       ((u8)0x60)
#define PRIORITY_7       ((u8)0x70)
#define PRIORITY_8       ((u8)0x80)
#define PRIORITY_9       ((u8)0x90)
#define PRIORITY_10      ((u8)0xA0)
#define PRIORITY_11      ((u8)0xB0)
#define PRIORITY_12      ((u8)0xC0)
#define PRIORITY_13      ((u8)0xD0)
#define PRIORITY_14      ((u8)0xE0)
#define PRIORITY_15      ((u8)0xF0)
#define PRIORITY_NA      ((u8)0x00)

/*
Interrupts ID Masks
*/
#define InterruptID_0           0  
#define InterruptID_1           1  
#define InterruptID_2           2  
#define InterruptID_3           3  
#define InterruptID_4           4  
#define InterruptID_5           5  
#define InterruptID_6           6  
#define InterruptID_7           7  
#define InterruptID_8           8  
#define InterruptID_9           9  
#define InterruptID_10          10 
#define InterruptID_11          11 
#define InterruptID_12          12 
#define InterruptID_13          13 
#define InterruptID_14          14 
#define InterruptID_15          15 
#define InterruptID_16          16 
#define InterruptID_17          17 
#define InterruptID_18          18 
#define InterruptID_19          19 
#define InterruptID_20          20 
#define InterruptID_21          21 
#define InterruptID_22          22 
#define InterruptID_23          23 
#define InterruptID_24          24 
#define InterruptID_25          25 
#define InterruptID_26          26 
#define InterruptID_27          27 
#define InterruptID_28          28 
#define InterruptID_29          29 
#define InterruptID_30          30 
#define InterruptID_31          31 
#define InterruptID_32          32 
#define InterruptID_33          33 
#define InterruptID_34          34 
#define InterruptID_35          35 
#define InterruptID_36          36 
#define InterruptID_37          37 
#define InterruptID_38          38 
#define InterruptID_39          39 
#define InterruptID_40          40 
#define InterruptID_41          41 
#define InterruptID_42          42 
#define InterruptID_43          43 
#define InterruptID_44          44 
#define InterruptID_45          45 
#define InterruptID_46          46 
#define InterruptID_47          47 
#define InterruptID_48          48 
#define InterruptID_49          49 
#define InterruptID_50          50 
#define InterruptID_51          51 
#define InterruptID_52          52 
#define InterruptID_53          53 
#define InterruptID_54          54 
#define InterruptID_55          55 
#define InterruptID_56          56 
#define InterruptID_57          57 
#define InterruptID_58          58 
#define InterruptID_59          59 
#define InterruptID_60          60 
#define InterruptID_61          61 
#define InterruptID_62          62 
#define InterruptID_63          63 
#define InterruptID_64          64 
#define InterruptID_65          65 
#define InterruptID_66          66 
#define InterruptID_67          67 
#define InterruptID_68          68 
#define InterruptID_69          69 
#define InterruptID_70          70 
#define InterruptID_71          71 
#define InterruptID_72          72 
#define InterruptID_73          73 
#define InterruptID_74          74 
#define InterruptID_75          75 
#define InterruptID_76          76 
#define InterruptID_77          77 
#define InterruptID_78          78 
#define InterruptID_79          79 
#define InterruptID_80          80 
#define InterruptID_81          81 
#define InterruptID_82          82 
#define InterruptID_83          83 
#define InterruptID_84          84 
#define InterruptID_85          85 
#define InterruptID_86          86 
#define InterruptID_87          87 
#define InterruptID_88          88 
#define InterruptID_89          89 
#define InterruptID_90          90 
#define InterruptID_91          91 
#define InterruptID_92          92 
#define InterruptID_93          93 
#define InterruptID_94          94 
#define InterruptID_95          95 
#define InterruptID_96          96 
#define InterruptID_97          97 
#define InterruptID_98          98 
#define InterruptID_99          99 
#define InterruptID_100         100
#define InterruptID_101         101
#define InterruptID_102         102
#define InterruptID_103         103
#define InterruptID_104         104
#define InterruptID_105         105
#define InterruptID_106         106
#define InterruptID_107         107
#define InterruptID_108         108
#define InterruptID_109         109
#define InterruptID_110         110
#define InterruptID_111         111
#define InterruptID_112         112
#define InterruptID_113         113
#define InterruptID_114         114
#define InterruptID_115         115
#define InterruptID_116         116
#define InterruptID_117         117
#define InterruptID_118         118
#define InterruptID_119         119
#define InterruptID_120         120
#define InterruptID_121         121
#define InterruptID_122         122
#define InterruptID_123         123
#define InterruptID_124         124
#define InterruptID_125         125
#define InterruptID_126         126
#define InterruptID_127         127
#define InterruptID_128         128
#define InterruptID_129         129
#define InterruptID_130         130
#define InterruptID_131         131
#define InterruptID_132         132
#define InterruptID_133         133
#define InterruptID_134         134
#define InterruptID_135         135
#define InterruptID_136         136
#define InterruptID_137         137
#define InterruptID_138         138
#define InterruptID_139         139
#define InterruptID_140         140
#define InterruptID_141         141
#define InterruptID_142         142
#define InterruptID_143         143
#define InterruptID_144         144
#define InterruptID_145         145
#define InterruptID_146         146
#define InterruptID_147         147
#define InterruptID_148         148
#define InterruptID_149         149
#define InterruptID_150         150
#define InterruptID_151         151
#define InterruptID_152         152
#define InterruptID_153         153
#define InterruptID_154         154
#define InterruptID_155         155
#define InterruptID_156         156
#define InterruptID_157         157
#define InterruptID_158         158
#define InterruptID_159         159
#define InterruptID_160         160
#define InterruptID_161         161
#define InterruptID_162         162
#define InterruptID_163         163
#define InterruptID_164         164
#define InterruptID_165         165
#define InterruptID_166         166
#define InterruptID_167         167
#define InterruptID_168         168
#define InterruptID_169         169
#define InterruptID_170         170
#define InterruptID_171         171
#define InterruptID_172         172
#define InterruptID_173         173
#define InterruptID_174         174
#define InterruptID_175         175
#define InterruptID_176         176
#define InterruptID_177         177
#define InterruptID_178         178
#define InterruptID_179         179
#define InterruptID_180         180
#define InterruptID_181         181
#define InterruptID_182         182
#define InterruptID_183         183
#define InterruptID_184         184
#define InterruptID_185         185
#define InterruptID_186         186
#define InterruptID_187         187
#define InterruptID_188         188
#define InterruptID_189         189
#define InterruptID_190         190
#define InterruptID_191         191
#define InterruptID_192         192
#define InterruptID_193         193
#define InterruptID_194         194
#define InterruptID_195         195
#define InterruptID_196         196
#define InterruptID_197         197
#define InterruptID_198         198
#define InterruptID_199         199
#define InterruptID_200         200
#define InterruptID_201         201
#define InterruptID_202         202
#define InterruptID_203         203
#define InterruptID_204         204
#define InterruptID_205         205
#define InterruptID_206         206
#define InterruptID_207         207
#define InterruptID_208         208
#define InterruptID_209         209
#define InterruptID_210         210
#define InterruptID_211         211
#define InterruptID_212         212
#define InterruptID_213         213
#define InterruptID_214         214
#define InterruptID_215         215
#define InterruptID_216         216
#define InterruptID_217         217
#define InterruptID_218         218
#define InterruptID_219         219
#define InterruptID_220         220
#define InterruptID_221         221
#define InterruptID_222         222
#define InterruptID_223         223
#define InterruptID_224         224
#define InterruptID_225         225
#define InterruptID_226         226
#define InterruptID_227         227
#define InterruptID_228         228
#define InterruptID_229         229
#define InterruptID_230         230
#define InterruptID_231         231
#define InterruptID_232         232
#define InterruptID_233         233
#define InterruptID_234         234
#define InterruptID_235         235
#define InterruptID_236         236
#define InterruptID_237         237
#define InterruptID_238         238
#define InterruptID_239         239





/*
Interrupts ID Masks
*/

#define EXTI_0       ((u64)0x00000001)
#define EXTI_1       ((u64)0x00000002)
#define EXTI_2       ((u64)0x00000004)
#define EXTI_3       ((u64)0x00000008)
#define EXTI_4       ((u64)0x00000010)
#define EXTI_5       ((u64)0x00000020)
#define EXTI_6       ((u64)0x00000040)
#define EXTI_7       ((u64)0x00000080)
#define EXTI_8       ((u64)0x00000100)
#define EXTI_9       ((u64)0x00000200)
#define EXTI_10      ((u64)0x00000400)
#define EXTI_11      ((u64)0x00000800)
#define EXTI_12      ((u64)0x00001000)
#define EXTI_13      ((u64)0x00002000)
#define EXTI_14      ((u64)0x00004000)
#define EXTI_15      ((u64)0x00008000)
#define EXTI_16      ((u64)0x00010000)
#define EXTI_17      ((u64)0x00020000)
#define EXTI_18      ((u64)0x00040000)
#define EXTI_19      ((u64)0x00080000)
#define EXTI_20      ((u64)0x00100000)
#define EXTI_21      ((u64)0x00200000)
#define EXTI_22      ((u64)0x00400000)
#define EXTI_23      ((u64)0x00800000)
#define EXTI_24      ((u64)0x01000000)
#define EXTI_25      ((u64)0x02000000)
#define EXTI_26      ((u64)0x04000000)
#define EXTI_27      ((u64)0x08000000)
#define EXTI_28      ((u64)0x10000000)
#define EXTI_29      ((u64)0x20000000)
#define EXTI_30      ((u64)0x40000000)
#define EXTI_31      ((u64)0x80000000)
#define EXTI_32      ((u64)0x0000000100000000)
#define EXTI_33      ((u64)0x0000000200000000)
#define EXTI_34      ((u64)0x0000000400000000)
#define EXTI_35      ((u64)0x0000000800000000)
#define EXTI_36      ((u64)0x0000001000000000)
#define EXTI_37      ((u64)0x0000002000000000)
#define EXTI_38      ((u64)0x0000004000000000)
#define EXTI_39      ((u64)0x0000008000000000)
#define EXTI_40      ((u64)0x0000010000000000)
#define EXTI_41      ((u64)0x0000020000000000)
#define EXTI_42      ((u64)0x0000040000000000)
#define EXTI_43      ((u64)0x0000080000000000)
#define EXTI_44      ((u64)0x0000100000000000)
#define EXTI_45      ((u64)0x0000200000000000)
#define EXTI_46      ((u64)0x0000400000000000)
#define EXTI_47      ((u64)0x0000800000000000)
#define EXTI_48      ((u64)0x0001000000000000)
#define EXTI_49      ((u64)0x0002000000000000)
#define EXTI_50      ((u64)0x0004000000000000)
#define EXTI_51      ((u64)0x0008000000000000)
#define EXTI_52      ((u64)0x0010000000000000)
#define EXTI_53      ((u64)0x0020000000000000)
#define EXTI_54      ((u64)0x0040000000000000)
#define EXTI_55      ((u64)0x0080000000000000)
#define EXTI_56      ((u64)0x0100000000000000)
#define EXTI_57      ((u64)0x0200000000000000)
#define EXTI_58      ((u64)0x0400000000000000)
#define EXTI_59      ((u64)0x0800000000000000)

/*                       
ProtoTypes of the Functions 
*/                       



extern void NVIC_EnableIRQ(u8 InterruptID);
extern void NVIC_DisableIRQ(u8 InterruptID);

extern void NVIC_SetPendingIRQ(u8 InterruptID);
extern void NVIC_ClearPendingIRQ(u8 InterruptID);
extern void NVIC_GetPendingState(u8 InterruptID, void * PendingState);

extern void SCB_SetPriorityGrouping(u32 Copy_PriorityConfig);

extern void NVIC_EnableAllIRQs(void);
extern void NVIC_DisableAllIRQs(void);

extern void NVIC_EnableFaults(void);
extern void NVIC_DisableFaults(void);

extern void NVIC_SetPriorityFilter(u8 Priority);
extern void NVIC_ClearPriorityFilter(void);

extern void NVIC_GenerateSoftwareIRQ(u8 InterruptID);

extern void NVIC_SetPriority(u8 InterruptID, u8 Priority);
extern void NVIC_GetPriority(u8 Copy_InterruptID, u8 * Copy_pPriority);

#endif
