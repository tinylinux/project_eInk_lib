################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Base_TP_II1.c \
../src/LED.c \
../src/MCUXpresso_cr_startup.c \
../src/MCUXpresso_crp.c \
../src/MCUXpresso_mtb.c \
../src/lib_ENS_II1_lcd.c \
../src/system.c 

OBJS += \
./src/Base_TP_II1.o \
./src/LED.o \
./src/MCUXpresso_cr_startup.o \
./src/MCUXpresso_crp.o \
./src/MCUXpresso_mtb.o \
./src/lib_ENS_II1_lcd.o \
./src/system.o 

C_DEPS += \
./src/Base_TP_II1.d \
./src/LED.d \
./src/MCUXpresso_cr_startup.d \
./src/MCUXpresso_crp.d \
./src/MCUXpresso_mtb.d \
./src/lib_ENS_II1_lcd.d \
./src/system.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DCR_INTEGER_PRINTF -D__USE_CMSIS -D__CODE_RED -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=256 -D__REDLIB__ -I"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/Base_TP_II1/inc" -I"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/peripherals_lib/inc" -I"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/utilities_lib/inc" -I"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/common/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


