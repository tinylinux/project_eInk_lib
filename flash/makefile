################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Base_TP_II1.axf

# Tool invocations
Base_TP_II1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/peripherals_lib/flash" -L"/home/tinylinux/Dev/MCUXpresso_11.4.1_6260/workspace/utilities_lib/flash" -Xlinker -Map="Base_TP_II1.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "Multi_Timer_Blinky_flash.ld" -o "Base_TP_II1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Base_TP_II1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Base_TP_II1.axf"; # arm-none-eabi-objcopy -v -O binary "Base_TP_II1.axf" "Base_TP_II1.bin" ; # checksum -p LPC804 -d "Base_TP_II1.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
