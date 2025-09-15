################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Real_time_clock.lss \

FLASH_IMAGE += \
Real_time_clock.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Real_time_clock.elf secondary-outputs

# Tool invocations
Real_time_clock.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Real_time_clock.map -mmcu=atmega16 -o "Real_time_clock.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Real_time_clock.lss: Real_time_clock.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Real_time_clock.elf  >"Real_time_clock.lss"
	@echo 'Finished building: $@'
	@echo ' '

Real_time_clock.hex: Real_time_clock.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Real_time_clock.elf  "Real_time_clock.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Real_time_clock.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Real_time_clock.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Real_time_clock.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
