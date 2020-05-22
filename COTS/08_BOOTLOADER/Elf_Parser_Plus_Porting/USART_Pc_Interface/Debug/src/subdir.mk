################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/dDMA.c \
../src/dGPIO.c \
../src/dNVIC.c \
../src/dRCC.c \
../src/dUSART.c \
../src/hUSART.c \
../src/main.c 

OBJS += \
./src/dDMA.o \
./src/dGPIO.o \
./src/dNVIC.o \
./src/dRCC.o \
./src/dUSART.o \
./src/hUSART.o \
./src/main.o 

C_DEPS += \
./src/dDMA.d \
./src/dGPIO.d \
./src/dNVIC.d \
./src/dRCC.d \
./src/dUSART.d \
./src/hUSART.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


